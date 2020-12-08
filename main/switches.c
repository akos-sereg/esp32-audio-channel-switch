#include "include/switches.h"

static xQueueHandle gpio_evt_queue = NULL;
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

int switch_in_comp_state = 0;
int switch_in_guitar_state = 0;
void listen_switches(void* arg)
{
    uint32_t io_num;
    int current_state;

    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            current_state = gpio_get_level(io_num);

            if (io_num == SWITCH_IN_COMP && switch_in_comp_state != current_state) {
                printf("GPIO[%d:comp] state changed: %d\n", io_num, current_state);
                switch_in_comp_state = current_state;
            }

            if (io_num == SWITCH_IN_GUITAR && switch_in_guitar_state != current_state) {
                printf("GPIO[%d:guitar] state changed: %d\n", io_num, current_state);
                switch_in_guitar_state = current_state;
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

    // create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    // start gpio task
    xTaskCreate(listen_switches, "listen_switches", (1024 * 32), NULL, 5, NULL);

    // install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // hook isr handler for specific gpio pin
    gpio_isr_handler_add(SWITCH_IN_COMP, gpio_isr_handler, (void*) SWITCH_IN_COMP);
    gpio_isr_handler_add(SWITCH_IN_GUITAR, gpio_isr_handler, (void*) SWITCH_IN_GUITAR);

    // remove isr handler for gpio number.
    gpio_isr_handler_remove(SWITCH_IN_COMP);
    gpio_isr_handler_remove(SWITCH_IN_GUITAR);

    // hook isr handler for specific gpio pin again
    gpio_isr_handler_add(SWITCH_IN_COMP, gpio_isr_handler, (void*) SWITCH_IN_COMP);
    gpio_isr_handler_add(SWITCH_IN_GUITAR, gpio_isr_handler, (void*) SWITCH_IN_GUITAR);
}