#include "global_config.h"
//************  VARIABLE DECEARATION *******************************************

int battPercent = 0;
float battVolt = 0.0;
float cell1 = 0.0;
float cell2 = 0.0;
float cell3 = 0.0;
float balUnit = 0.0;
float totalUnit = 0.0;
float usage = 0.0;
float solarVoltage = 0.0;
float solarCurrent = 0.0;
float acVolt = 0.0;
float acOut = 0.0;
float frequency = 0.0;
float powerFactor = 0.0;
float pwr = 0.0;
float chargeCurrent = 0.0;
int bckl = 0;
bool upsFlag;
bool bleFlag;
bool wifiScan = false;
const char *deviceLock;
String deviceControl = "";
const char *deviceMode = "";
const char *deviceState = "";
float storedConsumption;
const char *pwrBState  = "";
// ********************************************************************************

// // I2S Audio Output Pins (ESP32-S3)
// Audio audio;
// const int I2S_DOUT = 40; // Data Out (DAC)
// const int I2S_BCLK = 1;  // Bit Clock
// const int I2S_LRC = 2;
// ************** RTC ***************************************
// ************** RTC ***************************************
// RtcDS3231<TwoWire> Rtc(Wire);
// int hours, minutes, months, years, days, sec, hour24;
// char hourChar[3] = "00";
// char minuteChar[3] = "00";
// char dayTime[3] = "";

// *************************************************************

// **************** TIME LIB ********************
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
const char *time_zone = "WAT-1";
int hours, minutes, seconds, months, years, days, sec, hour24;
char hourChar[3] = "00";
char minuteChar[3] = "00";
char secc[3] = "00";
int ii = 0;
long new_millis = 0;
char timeYear[5] = "2024";
char timeMonth[3] = "1";
char timeDay[3] = "1";
char timeHour[3] = "1";
char timeMinute[3] = "1";
char timeSecond[3] = "00";
char timeWeek[4] = "Mon";

char timeOut[10] = "\0";
char dayTime[3];
// *******************************************

//  ************* PIN DECLEARATION *********************************

const int BCKL = 38;
const int relay =  40;
const int buzzer = 48;
const int nepaPin = 41;
bool wifiFlag = false;
bool keyFlag = false;
String list = "";
String newSsid = "";
String newPassword = "";
bool state = false;
int pwrCount = 0;
// LGFX display;
String incommingMessage = "";
String topic = "";
// ********************************************************************

// *************** WIfi & MQTT *************************
WiFiClient espClient;
// WiFiClientSecure espClient;
PubSubClient wifiMqtt(espClient);
bool wifiState = false;
bool connectedToNetwork = false;
// *********************************************************

// **************** UPTIME TRACKING ***********************************
long upTimePeriod = 0;
String initialTime = "";
bool timeCheck = false;
// ******************************************************************

// ******************* OTA UPDATE **************************************
float firmwareVersion;
const char *otaAction;
// ********************************************************************

// ******************** WIFI CONFIG****************************************
bool wifiConfigState = false;
// *************************************************************************

// ******************* BLE CONFIG ****************************************
bool bleConnected = false;
// ************************************************************************

const char *connectionPriority;
int screenNotify = 0;


// blue = 41
// green = 48
// white = 47
// yellow = 42