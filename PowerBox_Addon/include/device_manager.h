#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H
#include <Arduino.h>

#include "global_config.h"
#include "device_setup.h"

void deviceOperation();
void variableUpdate();
void initializeSerial();
void initializeFlashMemory();
void initializeBluetooth();
void initializeWiFi();
void initializeProcessManager();
void initializeRelay();   

void handleScreenAnimation();
void checkPowerStatus();
void manageWiFiConnection();
void notificationBegin();

#endif