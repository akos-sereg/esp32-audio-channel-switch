#include "include/relays.h"
#include "include/state.h"

void init_relays() {
    // init shift register gpios
    gpio_set_direction(LED_STRIP_LATCH_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_STRIP_CLOCK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_STRIP_DATA_GPIO, GPIO_MODE_OUTPUT);

    // init red led' gpio
    // gpio_set_direction(LED_STRIP_RED, GPIO_MODE_OUTPUT);
    // gpio_pad_select_gpio(LED_STRIP_RED);
}


void relays_refresh() {

    for (int i=0; i!=8; i++) {
        gpio_set_level(LED_STRIP_CLOCK_GPIO, 0);

        switch(i) {
            // computer (in)
            case 7:
                gpio_set_level(LED_STRIP_DATA_GPIO, app_state.relay_in_comp);
                break;

            // guitar (in)
            case 6:
                gpio_set_level(LED_STRIP_DATA_GPIO, app_state.relay_in_guitar);
                break;

            // vinyl (in)
            case 5:
                gpio_set_level(LED_STRIP_DATA_GPIO, app_state.relay_in_vinyl);
                break;

            // headphones (out)
            case 4:
                gpio_set_level(LED_STRIP_DATA_GPIO, app_state.is_muted ? 0 : app_state.relay_out_headphones);
                break;

            // speaker (out)
            case 3:
                gpio_set_level(LED_STRIP_DATA_GPIO, app_state.is_muted ? 0 : app_state.relay_out_speaker);
                break;

            // amplifier (out)
            case 2:
                gpio_set_level(LED_STRIP_DATA_GPIO, app_state.is_muted ? 0 : app_state.relay_out_amplifier);
                break;

            // dummy
            case 1:
                gpio_set_level(LED_STRIP_DATA_GPIO, 0);
                break;

            // dummy
            case 0:
                gpio_set_level(LED_STRIP_DATA_GPIO, 0);
                break;
        }

	    gpio_set_level(LED_STRIP_CLOCK_GPIO, 1);
    }

    gpio_set_level(LED_STRIP_LATCH_GPIO, 1);
    gpio_set_level(LED_STRIP_LATCH_GPIO, 0);
}