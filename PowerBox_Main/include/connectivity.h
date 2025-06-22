#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include <Arduino.h>
#include "device_setup.h"
#include "global_config.h"



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

#endif