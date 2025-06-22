#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <NimBLEDevice.h>
#include "global_config.h"
#include "device_setup.h"

// Define UUIDs for the BLE service and characteristics
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define TX_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define TTX_CHARACTERISTIC_UUID "beb5483e-36e2-4688-b7f5-ea07361b26a8"
#define RX_CHARACTERISTIC_UUID "beb5483f-36e1-4688-b7f5-ea07361b26a9"

extern NimBLEServer *pServer;
extern NimBLEService *pService;
extern NimBLECharacteristic *pTxCharacteristic;
extern NimBLECharacteristic *pTTxCharacteristic;
extern NimBLECharacteristic *pRxCharacteristic;

// Global variables to track connection status and incoming data

extern std::string dataIn;

// Class definition for the BLE functionality
class Ble
{
public:
    Ble();
    void Begin(const char *id);
    static void HandleBleCommand(const char *command);
    static void SendResponse(const char *type, const char *msg, const char *deviceId);

private:
    
};

#endif