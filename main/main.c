#include "include/main.h"
#include "include/relays.h"
#include "include/nvs-store.h"
#include "include/state.h"

void app_main(void)
{
    init_relays();
    init_switches();
    init_nvs_store();

    // read settings from nvs store
    state_set_input(get_nvs_value(NVS_KEY_IN_CHANNEL));
    state_set_output(get_nvs_value(NVS_KEY_OUT_CHANNEL));
    state_set_muted(get_nvs_value(NVS_KEY_MUTED));
    state_set_child_lock(gpio_get_level(GPIO_CHILDLOCK));
    relays_refresh();

    state_print();

    while (true) {

        // busy waiting
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}
