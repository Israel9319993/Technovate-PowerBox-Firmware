
#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

// #include "config.h"

#include <Arduino.h>
// #include <HardwareSerial.h>


//************  VARIABLE DECEARATION *******************************************
#include <ArduinoJson.h>
// GPIO17 as TX for UART2
extern float bmsCurrent, bmsVoltage, bmsSOC,bmsSOH, bmsRCC, bmsFCC;
extern const char* deviceState;
extern uint16_t chargeCycles;
extern const char* sign;

extern float balUnit ;
extern float totalUnit ;
extern float usage ;
extern float solarVoltage ;
extern float solarCurrent ;
extern String pwrBState;
extern float acVolt ;
extern float acOut ;
extern float power ;
extern float powerFactor ;
extern float frequency ;
extern float chargeCurrent ;
extern int bckl;
extern bool state;
extern int pwrCount;
extern bool upsFlag;
extern bool bleFlag;
extern const int BCKL;


extern bool wifiFlag;
extern bool keyFlag;
extern bool wifiScan;
// extern LGFX display; 
extern SemaphoreHandle_t xGuiSemaphore;
extern String newSsid;
extern String newPassword;

extern const char *deviceLock;
extern const char *deviceMode;
extern String deviceControl;
extern float storedConsumption;
// ********************************************************************************

// ******************* PIN DECLEARATION *********************************
#define relayPin 27
#define buzzer 12

#define pzemRx 18
#define pzemTx 5


#define RXD2 16 // GPIO16 as RX for UART2
#define TXD2 17 



// *************** Wifi & MQTT *************************
// #include <WiFiUdp.h>
#include <WiFi.h>
#include <PubSubClient.h>
// #include <WiFiClientSecure.h>
// extern WiFiClientSecure espClient;

#include <WiFiClient.h>
extern WiFiClient espClient;
extern PubSubClient wifiMqtt;
extern bool wifiState;
extern bool gsmState;
extern bool connectedToNetwork;
// *********************************************************

// ******************* OTA UPDATE **************************************
extern float firmwareVersion;
extern const char *otaAction;
// ********************************************************************
// ******************** WIFI CONFIG****************************************
extern bool wifiConfigState;
// *************************************************************************

// ******************* BLE CONFIG ****************************************
extern bool bleConnected;
// ************************************************************************


extern int screenNotify;



#endif