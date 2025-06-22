#ifndef TASK_H
#define TASK_H
#include <Arduino.h>
#include "device_setup.h"
#include "global_config.h"
#include <ArduinoJson.h>
#include "timer.h"
#include "ui.h"
#include "ui_events.h"
// #include "dispsetup.h"

// static uint32_t my_tick_get_cb (void) { return millis(); }

void readTask(void *pvParameter);
// void uiTask(void *pvParameters);
void scan_wifi_task(void *pvParameters);
void ui_event_keyboard(lv_event_t * e);
void connect_wifi_task(void *pvParameters);
void pushMsg(void *pvParameters);
void notificationTask(void *pvParameters);
void wifiScanTask(void *param);
void readEnergyTask(void *pvParameters);
void BLEPowerBoxSend(void *declaration);
void BLEPowerBoxConnect(void *declaration);
extern TaskHandle_t bleTaskHandle;
#endif