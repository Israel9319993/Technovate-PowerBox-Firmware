#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <Arduino.h>
#include "device_setup.h"
#include "global_config.h"
#include "lvgl.h"
#include "ui.h"
#include "global.h"

class Connection
{
public:
    Connection();
    void WifiBegin(const char *ssid, const char *password);
    void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);    // Add static
    void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info); // Add static
    void WifiMqttConfig();
   

private:
    const char *_ssid;
    const char *_password;
};


void event_handler(lv_event_t *e);
void ui_event_keyboard(lv_event_t *e);
#endif