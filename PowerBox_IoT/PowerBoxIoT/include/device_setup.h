#ifndef DEVICE_SETUP_H
#define DEVICE_SETUP_H
#include <Arduino.h>
// Declare the WiFiCredentials structure
struct WiFiCredentials
{
    const char *ssid;
    const char *password;
};

// Declare the MQTTConfig structure
struct MQTTConfig
{
    const char *publishTopic;
    const char *wallet;
    const char *autoBilling;
    const char *threshold;
    const char *control;
    const char *response;
    const char *config;
    const char *event;
    const char *otaUpdate;

    const char *willTopic;
    int willQos;
    bool willRetain;
    const char *willMessage;
    bool clearSession;
};

// Extern declarations for WiFiCredentials and MQTTConfig
extern WiFiCredentials wifiCredentials;
extern MQTTConfig mqttConfig;
extern String deviceId;
extern const char* mqttUserName;
extern const char* mqttPassword;
extern const char* mqttServer;
extern  double port;
extern double lastUploadedTime;
extern const int postingInterval;
extern const char* token;
extern float oldFirmwareVersion;
extern float newFirmwareVersion;
extern const char *otaBaseUrl;

#endif