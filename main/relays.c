/*
  Relays are connected to a SN74HC595 shift register, which is driven by ESP32.
*/

#include "include/relays.h"
#include "include/state.h"

void init_relays() {
    // init shift register gpios
    gpio_set_direction(SHIFT_REGISTER_LATCH_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(SHIFT_REGISTER_CLOCK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(SHIFT_REGISTER_DATA_GPIO, GPIO_MODE_OUTPUT);
}


void relays_refresh() {

    for (int i=0; i!=8; i++) {
        gpio_set_level(SHIFT_REGISTER_CLOCK_GPIO, 0);

        switch(i) {
            case 0: gpio_set_level(SHIFT_REGISTER_DATA_GPIO, 0); break;
            case 1: gpio_set_level(SHIFT_REGISTER_DATA_GPIO, 0); break;
            case 2: gpio_set_level(SHIFT_REGISTER_DATA_GPIO, app_state.is_muted ? 0 : app_state.relay_out_amplifier); break;
            case 3: gpio_set_level(SHIFT_REGISTER_DATA_GPIO, app_state.is_muted ? 0 : app_state.relay_out_speaker); break;
            case 4: gpio_set_level(SHIFT_REGISTER_DATA_GPIO, app_state.is_muted ? 0 : app_state.relay_out_headphones); break;
            case 5: gpio_set_level(SHIFT_REGISTER_DATA_GPIO, app_state.relay_in_vinyl); break;
            case 6: gpio_set_level(SHIFT_REGISTER_DATA_GPIO, app_state.relay_in_guitar); break;
            case 7: gpio_set_level(SHIFT_REGISTER_DATA_GPIO, app_state.relay_in_comp); break;
        }

	    gpio_set_level(SHIFT_REGISTER_CLOCK_GPIO, 1);
    }

    gpio_set_level(SHIFT_REGISTER_LATCH_GPIO, 1);
    gpio_set_level(SHIFT_REGISTER_LATCH_GPIO, 0);
}