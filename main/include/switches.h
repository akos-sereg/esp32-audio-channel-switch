#ifndef __switches_h_included__
#define __switches_h_included__

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define SWITCH_IN_COMP  18
#define SWITCH_IN_GUITAR  19

#define GPIO_INPUT_PIN_SEL  ((1ULL<<SWITCH_IN_COMP) | (1ULL<<SWITCH_IN_GUITAR))
#define ESP_INTR_FLAG_DEFAULT 0

/**
  Listen for button / switch update events
*/
extern void listen_switches(void* arg);

/**
  Configure button / switch GPIOs
*/
extern void init_switches();

/**
  Reads the current state of button / switches - useful at boot time
*/
extern void read_switch_states();

#endif