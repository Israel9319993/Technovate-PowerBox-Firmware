#include "connectivity.h"

Connection::Connection() {}

void Connection::WifiBegin(const char *ssid, const char *password)
{
    _ssid = ssid;
    _password = password;
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);

    // Bind instance methods using lambdas
    WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info)
                 { this->WiFiStationConnected(event, info); }, ARDUINO_EVENT_WIFI_STA_CONNECTED);

    WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info)
                 { this->WiFiStationDisconnected(event, info); }, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

    //   Serial.println(rootca);

    //  espClient.setCertificate(cert);
    //  Serial.println(cert);

    //  espClient.setPrivateKey(privatekey);
    //  Serial.println(privatekey);

    //  espClient.setInsecure();

    // // Connect to the server securely without certificates
    // if ( espClient.connect(mqtt_server,  8883)) {
    //     Serial.println("Connected to server successfully!");
    //     // You can now send/receive data securely
    // } else {
    //     Serial.println("Connection failed.");
    // // }

    // client.setServer(MQTTConfig.mqttServer, 1883);
    // client.setCallback(callback);
    // client.setBufferSize(6000);
}

void Connection::WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    wifiState = true;
    Serial.println("Connected to AP successfully!");
}

void Connection::WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    wifiState = false;
    // Serial.println("Disconnected from AP, trying to reconnect...");
    WiFi.begin(_ssid, _password); // Attempt reconnection
    connectedToNetwork = false;
}
