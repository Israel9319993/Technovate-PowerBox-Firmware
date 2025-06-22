#include "global_config.h"
//************  VARIABLE DECEARATION *******************************************


float bmsCurrent = 0.0;
float bmsVoltage = 0.0;
float bmsSOC = 0.0;
float bmsSOH = 0.0;
float bmsRCC = 0.0;
float bmsFCC = 0.0;
const char* deviceState = ""; // Initialize deviceState to "OFF"

uint16_t chargeCycles = 0; // Initialize chargeCycles to 0
const char* sign;

float balUnit = 0.0;
float totalUnit = 0.0;
float usage = 0.0;
float previousUsage = 0.0;
float initialUsage = 0.0;
float solarVoltage = 0.0;
float solarCurrent = 0.0;
float acVolt = 0.0;
float acOut = 0.0;
float power = 0.0;
float powerFactor = 0.0;
float frequency = 0.0;
float chargeCurrent = 0.0;

bool wifiScan = false;
String deviceControl = "";
const char *deviceLock = "";
const char *deviceMode = "";
float storedConsumption;
String pwrBState  = "";

// *************************************************************


//  ************* PIN DECLEARATION *********************************
#define relayPin 27
#define buzzer 12

#define pzemRx 18
#define pzemTx 5


#define RXD2 16 // GPIO16 as RX for UART2
#define TXD2 17 // GPIO17 as TX for UART2



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

int screenNotify = 0;

uint64_t  lastTime = 0;

// blue = 41
// green = 48
// white = 47
// yellow = 42