
#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

// #include "config.h"

#include <Arduino.h>
// #include <HardwareSerial.h>


//************  VARIABLE DECEARATION *******************************************
#include <ArduinoJson.h>
extern int battPercent;
extern float battVolt ;
extern float cell1 ;
extern float cell2 ;
extern float cell3 ;
extern float battVolt ;
extern float battVolt ;
extern float balUnit ;
extern float totalUnit ;
extern float usage ;
extern float solarVoltage ;
extern float solarCurrent ;
extern const char* pwrBState;
extern float acVolt ;
extern float acOut ;
extern float frequency ;
extern float powerFactor ;
extern float pwr ;
extern float chargeCurrent ;
extern int bckl;
extern bool state;
extern int pwrCount;
extern bool upsFlag;
extern bool bleFlag;
extern const int BCKL;
extern const int relay;
extern const int buzzer;
extern const int nepaPin;
extern bool wifiFlag;
extern bool keyFlag;
extern bool wifiScan;
// extern LGFX display; 
extern SemaphoreHandle_t xGuiSemaphore;
extern String newSsid;
extern String newPassword;

extern const char *deviceLock;
extern String deviceControl;
extern const char *deviceMode;
extern const char *deviceState;
extern float storedConsumption;
// ********************************************************************************


// I2S Audio Output Pins (ESP32-S3)
// #include <Audio.h>
// extern Audio audio;
// // extern const int I2S_DOUT;  // Data Out (DAC)
// extern const int I2S_BCLK;   // Bit Clock
// extern const int I2S_LRC;    // Left/Right Clock
// ************** RTC ***************************************
// #include <Wire.h> // must be included here so that Arduino library object file references work
// #include <RtcDS3231.h>
// extern RtcDS3231<TwoWire> Rtc;
// extern int hours, minutes, months, years, days, sec, hour24;
// extern char hourChar[3];
// extern char minuteChar[3];
// extern char dayTime[3];
// *************************************************************
//  ************ TIME LIB *************************
#include <TimeLib.h>
#include "time.h"
#include "esp_sntp.h"
#include <NTPClient.h>
extern const char* ntpServer1;
extern const char* ntpServer2;
extern const long  gmtOffset_sec;
extern const int   daylightOffset_sec;
extern const char* time_zone;


extern int hours, minutes, seconds, months, years, days, sec, hour24;
extern char hourChar[3] ;
extern char minuteChar[3];
extern char secc[3] ;
extern int ii ;
extern long new_millis;
extern char timeYear[5];
extern char timeMonth[3];
extern char timeDay[3];
extern char timeHour[3];
extern char timeMinute[3];
extern char timeSecond[3];
extern char timeWeek[4];

extern char timeOut[10];
extern char dayTime[3];

//  **********************************************

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

extern const char* connectionPriority;

extern int screenNotify;



#endif