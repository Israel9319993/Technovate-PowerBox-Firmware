#include <Arduino.h>
#include "global_config.h"
#include "bms_read.h"
#include "device_manager.h"
#include "inverter_read.h"


ReadBMS bms; // Create an instance of the ReadBMS class
InverterComm inverter(&Serial2, 16, 17); // Create an instance of the InverterComm class with Serial
void setup()
{
  Serial.begin(115200);
  inverter.begin(2400); // Initialize inverter communication at 2400 baud rate
  // bms.BMSInit(RXD2, TXD2, 9600); // Initialize BMS with RXD2 and TXD2 pins and 9600 baud rate
  // initializeSerial();
  // initializeRelay();
  initializeFlashMemory();
  lastTime = esp_timer_get_time(); // Initialize lastMicros to current time
  // initializeBluetooth();
  // initializeWiFi();
  // initializeProcessManager();
  // notificationBegin();
  
  // Test basic commands
  // if(inverter.enablePowerSaving(true)) {
  //   Serial.println("Power saving enabled");
  // } else {
  //   Serial.println("Failed to enable power saving");
  // }

  // if(inverter.setOutputSourcePriority(0)) {
  //   Serial.println("Output source priority set to 1");
  // } else {
  //   Serial.println("Failed to set output source priority");
  // }
  // Serial.println("Protocol ID: " + inverter.getProtocolID());
  // Serial.println("Serial Number: " + inverter.getSerialNumber());
  // Serial.println("Firmware Version: " + inverter.getFirmwareVersion());
  Serial.println("Device Mode: " + inverter.getDeviceMode());

// if(inverter.setMaxUtilityChargingCurrent(20)) {
//     Serial.println("Max charging current set to 100A");
//   } else {
//     Serial.println("Failed to set max charging current");
//   }

  // delay(1000); // Wait for 1 second to ensure settings are applied
  // Get device rating info
  DeviceRatingInfo ratingInfo;
  if (inverter.getDeviceRatingInfo(ratingInfo)) {
    inverter.printRatingInfo(ratingInfo);
  } else {
    Serial.println("Failed to get rating info");
  }

}

void loop()
{

   GeneralStatusInfo statusInfo;
  if (inverter.getGeneralStatus(statusInfo)) {
    inverter.printDeviceStatus(statusInfo);
  }
else {
    Serial.println("Failed to get rating info");
  }

  
  // Serial.printf("battery error status: %s\n", String(inverter.decodeErrors(inverter.getWarningStatus())).c_str());

    int errorCount;
  String* errorNames = inverter.getActiveErrorNames(inverter.getWarningStatus(), errorCount);
  Serial.printf("\nActive Errors (%d total):\n", errorCount);
  for (int i = 0; i < errorCount; i++) {
    Serial.printf("  %d: %s\n", i+1, errorNames[i].c_str());
  }
//     Serial.println("Device Mode: " + inverter.getDeviceMode());
//     delay(1000); // Delay for 1 second before the next loop iteration
  // variableUpdate();
  // deviceOperation();
  // manageWiFiConnection();
  // bms.readModbusResponse(); // Read the Modbus response from the BMS
  // vTaskDelay(1000 / portTICK_PERIOD_MS);
  
delay(1000);
}

// #include "driver/uart.h"


// const byte dataToSend[] = {0x51, 0x50, 0x49, 0x52, 0x49, 0xF8, 0x54, 0x0D};
// unsigned long lastSendtime = 0;
// const unsigned long interval = 2000;  // 2 seconds

// void setup() {
//   Serial.begin(115200);  // For debugging
//   Serial2.begin(2400, SERIAL_8N1, 16, 17);  // Adjust pins if needed
//     // uart_set_line_inverse(UART_NUM_2, UART_SIGNAL_RXD_INV | UART_SIGNAL_TXD_INV);

//   Serial.println("Starting Serial2 communication...");
// }

// void loop() {
//   unsigned long currentTime = millis();

//   // Send every 2 seconds
//   if (currentTime - lastSendtime >= interval) {
//     Serial2.write(dataToSend, sizeof(dataToSend));
//     Serial.println("Sent data:");
//     for (byte b : dataToSend) {
//       Serial.print("0x");
//       if (b < 0x10) Serial.print("0");
//       Serial.print(b, HEX);
//       Serial.print(" ");
//     }
//     Serial.println();
//     lastSendtime = currentTime;
//   }

//   // Check if response is available
//   if (Serial2.available()) {
//     Serial.println("Received response:");
//     while (Serial2.available()) {
//       byte b = Serial2.read();
//       Serial.print("0x");
//       if (b < 0x10) Serial.print("0");
//       Serial.print(b, HEX);
//       Serial.print(" ");
//     }
//     Serial.println();
//   }
//   delay(1000);  // Small delay to avoid flooding the serial output
// }
