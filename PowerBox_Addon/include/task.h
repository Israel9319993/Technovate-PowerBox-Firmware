#ifndef TASK_H
#define TASK_H
#include <Arduino.h>
#include "device_setup.h"
#include "global_config.h"
#include <ArduinoJson.h>

// #include "dispsetup.h"

// static uint32_t my_tick_get_cb (void) { return millis(); }

void readTask(void *pvParameter);
// void uiTask(void *pvParameters);
void scan_wifi_task(void *pvParameters);
void connect_wifi_task(void *pvParameters);
void pushMsg(void *pvParameters);
void notificationTask(void *pvParameters);
void readEnergyTask(void *pvParameters);
#endif