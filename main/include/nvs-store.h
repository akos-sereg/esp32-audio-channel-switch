#ifndef __nvs_store_h_included__
#define __nvs_store_h_included__

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#define NVS_VAL_IN_COMP 0
#define NVS_VAL_IN_GUITAR 1
#define NVS_VAL_IN_VINYL 2

#define NVS_VAL_OUT_HEADPHONES 0
#define NVS_VAL_OUT_SPEAKER 1
#define NVS_VAL_OUT_AMPLIFIER 2

extern void init_nvs_store();
extern void set_nvs_value(char *key, int32_t value);
extern int32_t get_nvs_value(char *key);
extern void nvs_shutdown();

nvs_handle_t app_nvs_handle;
esp_err_t nvs_error;
int nvs_flash_is_open;

char *NVS_KEY_IN_CHANNEL;
char *NVS_KEY_OUT_CHANNEL;
char *NVS_KEY_MUTED;

#endif