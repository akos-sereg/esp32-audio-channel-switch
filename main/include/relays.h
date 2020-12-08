#ifndef __relays_h_included__
#define __relays_h_included__

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_STRIP_LATCH_GPIO	32
#define LED_STRIP_DATA_GPIO	25
#define LED_STRIP_CLOCK_GPIO	33

extern void init_relays();
extern void relays_refresh(int value);

#endif