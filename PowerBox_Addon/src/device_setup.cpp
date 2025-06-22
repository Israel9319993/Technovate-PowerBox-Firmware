#include "device_setup.h"

// Define the WiFiCredentials structure
WiFiCredentials wifiCredentials = {
    // .ssid = "Israel's Galaxy S20 FE 5G",
    // .password = "64646464.1"

    //    .ssid = "ISWLOS_ENGINEERING",
    // .password = "pathw@y2noleg3"
    .ssid = "",
    .password = ""
    };

// Define the MQTTConfig structure
MQTTConfig mqttConfig = {
    .publishTopic = "POWERBOX/READING/",
    .wallet = "POWERBOX/WALLET/",
    .control = "POWERBOX/CONTROL/",
    .response = "POWERBOX/RESPONSE/",
    .config = "POWERBOX/CONFIG/",
    .otaUpdate = "POWERBOX/SINGLE_PHASE/OTA/UPDATE/",
    .willTopic = "POWERBOX/STATUS/",
    .willQos = 0,
    .willRetain = true,
    .willMessage = "offline",
    .clearSession = true,
    //   .port =   8883 //1883
};

String deviceId;
const char *mqttUserName = deviceId.c_str();
const char *mqttPassword = "powerBox";
const char *mqttServer = "41.223.145.80";

double port = 1883;
const char *token;
double lastUploadedTime = 0;
const int postingInterval = 5000;
float oldFirmwareVersion;
float newFirmwareVersion;

// const char *otaBaseUrl = "https://inv-online-isw.taildde2b.ts.net/firmware/test/single_phase/";