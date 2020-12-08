#include "include/relays.h"

void engine_load_init() {
    // init shift register gpios
    gpio_set_direction(LED_STRIP_LATCH_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_STRIP_CLOCK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_STRIP_DATA_GPIO, GPIO_MODE_OUTPUT);

    // init red led' gpio
    // gpio_set_direction(LED_STRIP_RED, GPIO_MODE_OUTPUT);
    // gpio_pad_select_gpio(LED_STRIP_RED);
}


/* value from 0 to 9 */
void led_strip_set(int value) {

    if (value < 0 || value > 9) {
        return;
    }

    for (int i=0; i!=8; i++) {
        gpio_set_level(LED_STRIP_CLOCK_GPIO, 0);
        gpio_set_level(LED_STRIP_DATA_GPIO, (7 - value) < i ? 1 : 0);
	    gpio_set_level(LED_STRIP_CLOCK_GPIO, 1);
    }

    gpio_set_level(LED_STRIP_LATCH_GPIO, 1);
    gpio_set_level(LED_STRIP_LATCH_GPIO, 0);
}