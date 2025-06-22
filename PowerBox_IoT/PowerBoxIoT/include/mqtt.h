#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include "global_config.h"
#include "device_setup.h"

void setupMQTT(PubSubClient &client);
String pushMessage();
bool publishMessage(PubSubClient &client, const char *topic, const char *payload);
String offLineMsg(bool stste);
void reconnect(PubSubClient &client);
void mqttConnect(PubSubClient &client);
void callback(PubSubClient &client, char *topic, byte *payload, unsigned int length);
const char *formatFloatToString(float value);
void sendResponse(PubSubClient &client, const char *type, const char *msg, const char *id);
void handleCommand(PubSubClient &client, const char *command);


#endif