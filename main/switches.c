#include "include/switches.h"
#include "include/state.h"
#include "include/relays.h"
#include "include/nvs-store.h"

static xQueueHandle gpio_evt_queue = NULL;
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

void listen_switches(void* arg)
{
    uint32_t io_num;
    int current_state;

    int in_comp_keypress = 0;
    int in_guit_keypress = 0;
    int in_viny_keypress = 0;
    int out_headphones_keypress = 0;
    int out_speaker_keypress = 0;
    int out_amplifier_keypress = 0;
    int is_muted_keypress = 0;

    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            current_state = gpio_get_level(io_num);

            // ------------------------------------------------------------------------------
            // Input channels
            // ------------------------------------------------------------------------------
            if (io_num == SWITCH_IN_COMP && in_comp_keypress != current_state) {
                printf("GPIO[%d:comp] state changed: %d\n", io_num, current_state);

                // rising edge
                if (current_state == 1) {
                    state_set_input(NVS_VAL_IN_COMP);
                    set_nvs_value(NVS_KEY_IN_CHANNEL, NVS_VAL_IN_COMP);
                    relays_refresh();
                    state_print();
                }

                in_comp_keypress = current_state;
            }

            if (io_num == SWITCH_IN_GUITAR && in_guit_keypress != current_state) {
                printf("GPIO[%d:guitar] state changed: %d\n", io_num, current_state);

                // rising edge
                if (current_state == 1) {
                    state_set_input(NVS_VAL_IN_GUITAR);
                    set_nvs_value(NVS_KEY_IN_CHANNEL, NVS_VAL_IN_GUITAR);
                    relays_refresh();
                    state_print();
                }

                in_guit_keypress = current_state;
            }

            if (io_num == SWITCH_IN_VINYL && in_viny_keypress != current_state) {
                printf("GPIO[%d:vinyl] state changed: %d\n", io_num, current_state);

                // rising edge
                if (current_state == 1) {
                    state_set_input(NVS_VAL_IN_VINYL);
                    set_nvs_value(NVS_KEY_IN_CHANNEL, NVS_VAL_IN_VINYL);
                    relays_refresh();
                    state_print();
                }

                in_viny_keypress = current_state;
            }

            // ------------------------------------------------------------------------------
            // Output channels
            // ------------------------------------------------------------------------------

            if (io_num == SWITCH_OUT_HEADPHONES && out_headphones_keypress != current_state) {
                printf("GPIO[%d:headphones] state changed: %d\n", io_num, current_state);

                // rising edge
                if (current_state == 1) {
                    state_set_output(NVS_VAL_OUT_HEADPHONES);
                    set_nvs_value(NVS_KEY_OUT_CHANNEL, NVS_VAL_OUT_HEADPHONES);
                    relays_refresh();
                    state_print();
                }

                out_headphones_keypress = current_state;
            }

            if (io_num == SWITCH_OUT_SPEAKER && out_speaker_keypress != current_state) {
                printf("GPIO[%d:speaker] state changed: %d\n", io_num, current_state);

                // rising edge
                if (current_state == 1) {
                    state_set_output(NVS_VAL_OUT_SPEAKER);
                    set_nvs_value(NVS_KEY_OUT_CHANNEL, NVS_VAL_OUT_SPEAKER);
                    relays_refresh();
                    state_print();
                }

                out_speaker_keypress = current_state;
            }

            if (io_num == SWITCH_OUT_AMPLIFIER && out_amplifier_keypress != current_state) {
                printf("GPIO[%d:amplifier] state changed: %d\n", io_num, current_state);

                // rising edge
                if (current_state == 1) {
                    state_set_output(NVS_VAL_OUT_AMPLIFIER);
                    set_nvs_value(NVS_KEY_OUT_CHANNEL, NVS_VAL_OUT_AMPLIFIER);
                    relays_refresh();
                    state_print();
                }

                out_amplifier_keypress = current_state;
            }

            // ------------------------------------------------------------------------------
            // Other buttons
            // ------------------------------------------------------------------------------

            if (io_num == GPIO_MUTE && is_muted_keypress != current_state) {
                printf("GPIO[%d:mute] state changed: %d\n", io_num, current_state);

                // rising edge
                if (current_state == 1) {
                    state_set_muted(app_state.is_muted == 1 ? 0 : 1);
                    set_nvs_value(NVS_KEY_MUTED, app_state.is_muted);
                    relays_refresh();
                    state_print();
                }

                is_muted_keypress = current_state;
            }

            if (io_num == GPIO_CHILDLOCK && app_state.child_lock != current_state) {
                printf("GPIO[%d:childlock] state changed: %d\n", io_num, current_state);
                app_state.child_lock = current_state;
                state_print();
            }
        }
    }
}

void init_switches() {
    gpio_config_t io_conf;

    // disable interrupt
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;

    // set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;

    // interrupt of rising edge
    io_conf.intr_type = GPIO_PIN_INTR_POSEDGE;

    // bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;

    // set as input mode
    io_conf.mode = GPIO_MODE_INPUT;

    // enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    // change gpio intrrupt type for one pin
    gpio_set_intr_type(SWITCH_IN_COMP, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(SWITCH_IN_GUITAR, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(SWITCH_IN_VINYL, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(SWITCH_OUT_HEADPHONES, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(SWITCH_OUT_SPEAKER, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(SWITCH_OUT_AMPLIFIER, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(GPIO_MUTE, GPIO_INTR_ANYEDGE);
    gpio_set_intr_type(GPIO_CHILDLOCK, GPIO_INTR_ANYEDGE);

    // create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    // start gpio task
    xTaskCreate(listen_switches, "listen_switches", (1024 * 32), NULL, 5, NULL);

    // install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // hook isr handler for specific gpio pin
    gpio_isr_handler_add(SWITCH_IN_COMP, gpio_isr_handler, (void*) SWITCH_IN_COMP);
    gpio_isr_handler_add(SWITCH_IN_GUITAR, gpio_isr_handler, (void*) SWITCH_IN_GUITAR);
    gpio_isr_handler_add(SWITCH_IN_VINYL, gpio_isr_handler, (void*) SWITCH_IN_VINYL);
    gpio_isr_handler_add(SWITCH_OUT_HEADPHONES, gpio_isr_handler, (void*) SWITCH_OUT_HEADPHONES);
    gpio_isr_handler_add(SWITCH_OUT_SPEAKER, gpio_isr_handler, (void*) SWITCH_OUT_SPEAKER);
    gpio_isr_handler_add(SWITCH_OUT_AMPLIFIER, gpio_isr_handler, (void*) SWITCH_OUT_AMPLIFIER);
    gpio_isr_handler_add(GPIO_MUTE, gpio_isr_handler, (void*) GPIO_MUTE);
    gpio_isr_handler_add(GPIO_CHILDLOCK, gpio_isr_handler, (void*) GPIO_CHILDLOCK);

    // remove isr handler for gpio number.
    gpio_isr_handler_remove(SWITCH_IN_COMP);
    gpio_isr_handler_remove(SWITCH_IN_GUITAR);
    gpio_isr_handler_remove(SWITCH_IN_VINYL);
    gpio_isr_handler_remove(SWITCH_OUT_HEADPHONES);
    gpio_isr_handler_remove(SWITCH_OUT_SPEAKER);
    gpio_isr_handler_remove(SWITCH_OUT_AMPLIFIER);
    gpio_isr_handler_remove(GPIO_MUTE);
    gpio_isr_handler_remove(GPIO_CHILDLOCK);

    // hook isr handler for specific gpio pin again
    gpio_isr_handler_add(SWITCH_IN_COMP, gpio_isr_handler, (void*) SWITCH_IN_COMP);
    gpio_isr_handler_add(SWITCH_IN_GUITAR, gpio_isr_handler, (void*) SWITCH_IN_GUITAR);
    gpio_isr_handler_add(SWITCH_IN_VINYL, gpio_isr_handler, (void*) SWITCH_IN_VINYL);
    gpio_isr_handler_add(SWITCH_OUT_HEADPHONES, gpio_isr_handler, (void*) SWITCH_OUT_HEADPHONES);
    gpio_isr_handler_add(SWITCH_OUT_SPEAKER, gpio_isr_handler, (void*) SWITCH_OUT_SPEAKER);
    gpio_isr_handler_add(SWITCH_OUT_AMPLIFIER, gpio_isr_handler, (void*) SWITCH_OUT_AMPLIFIER);
    gpio_isr_handler_add(GPIO_MUTE, gpio_isr_handler, (void*) GPIO_MUTE);
    gpio_isr_handler_add(GPIO_CHILDLOCK, gpio_isr_handler, (void*) GPIO_CHILDLOCK);
}