#include <Arduino.h>
#include "global_config.h"
#include "bms_read.h"
#include "device_manager.h"


ReadBMS bms; // Create an instance of the ReadBMS class
void setup()
{
  Serial.begin(115200);
  
  bms.BMSInit(RXD2, TXD2, 9600); // Initialize BMS with RXD2 and TXD2 pins and 9600 baud rate
  initializeSerial();
  initializeRelay();
  initializeFlashMemory();
  initializeBluetooth();
  initializeWiFi();
  initializeProcessManager();
  notificationBegin();
}

void loop()
{

  variableUpdate();
  deviceOperation();
  manageWiFiConnection();
  bms.readModbusResponse(); // Read the Modbus response from the BMS
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

