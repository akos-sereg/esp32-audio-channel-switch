#ifndef __relays_h_included__
#define __relays_h_included__

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define SHIFT_REGISTER_LATCH_GPIO	32
#define SHIFT_REGISTER_DATA_GPIO	25
#define SHIFT_REGISTER_CLOCK_GPIO	33

extern void init_relays();
extern void relays_refresh();

#endif