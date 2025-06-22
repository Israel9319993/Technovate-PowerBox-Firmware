#ifndef GLOBAL_H
#define GLOBAL_H
#include <Arduino.h>
//  #include "disp.h"

 
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
extern float acVolt ;
extern float acOut ;
extern float pwr ;
extern float chargeCurrent ;
extern int bckl;
extern bool state;
extern bool upsFlag;
extern bool bleFlag;
extern bool wifiScan;


extern const int BCKL;
extern const int relay;
extern bool wifiFlag;
extern bool keyFlag;
// extern LGFX display; 
extern SemaphoreHandle_t xGuiSemaphore;
// extern const char* newSsid;
// extern const char* newPassword;



#endif