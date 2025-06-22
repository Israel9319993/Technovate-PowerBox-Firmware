#include "connectivity.h"
#include "proccess_manager.h"
#include "energy_module.h"
#include "flash_memory.h"
#include "mqtt.h"
#include "buzzer_alert.h"
#include "device_manager.h"
#include "bluetooth.h"
#include "relay_control.h"
#include "notification.h"

EnergySensor readPzem(5, 18);

Connection connection;
Buzzer buzzerAlert;
Flash flash;
Ble bluetooth;
Relay relay;
Notification notify;

void initializeSerial()
{
  Serial.begin(115200); // Start serial communication at 115200 baud rate
  // Serial2.begin(2400, SERIAL_8E1);  // Uncomment to start communication with the meter
}

void initializeFlashMemory()
{
  flash.Begin();

  // bool formatted = SPIFFS.format();

  //       if (formatted)
  //       {
  //           Serial.println(F("\n\nSuccess formatting"));
  //           ESP.restart();
  //       }
  //       else
  //       {
  //           Serial.println(F("\n\nError formatting"));
  //       }

}


void notificationBegin()
{
  notify.begin(); // Initialize notification system
}



void initializeBluetooth()
{
  bluetooth.Begin(deviceId.c_str());
}

void initializeWiFi()
{
  connection.WifiBegin(wifiCredentials.ssid, wifiCredentials.password); // Connect to Wi-Fi
  setupMQTT(wifiMqtt);
}

void initializeProcessManager()
{
  processInit();
  buzzerAlert.PlayIntro(); // Play intro sound
}

void manageWiFiConnection()
{
  if (wifiState)
  {

    mqttConnect(wifiMqtt);
  }
}

void deviceOperation()
{

  acVolt = readPzem.GetVoltage();
  // current = readPzem.GetCurrent();
  power = readPzem.GetPower();
  frequency = readPzem.GetFrequency();
  usage = readPzem.GetEnergy();
  powerFactor = readPzem.GetPowerFactor();

  pwrBState = relay.GetState(); // Get the state of the relay


  if (strcmp(deviceMode, "prepaid") == 0)
  {
    balUnit = totalUnit - usage;
  }
  else
  {
    balUnit = 0;
    totalUnit = 0;
  }

  // totalUse = energyConsumption + storedConsumption;

  if (balUnit <= 0 && strcmp(deviceMode, "prepaid") == 0)
  {
    //   if(digitalRead(NepaDetect) == HIGH && ReadConsump !=0 ){
    balUnit = 0;

    buzzerAlert.PlayWarning();
    // pwrBState = "off";
    relay.MeterOff();
    // }
  }

  else
  {
    if (strcmp(deviceLock, "unlock") == 0 ){
      pwrBState = relay.GetState(); 
     if (deviceControl == "on")
    {
      relay.MeterOn();
    }

    else if (deviceControl == "off")
    {
      relay.MeterOff();
    }
  }
    
    else if (strcmp(deviceLock, "lock") == 0)
    {
      pwrBState = "lock";
      relay.MeterOff();
    }
  }
}


void initializeRelay()
{
  relay.Begin();
  relay.MeterOn(); // Turn off the relay initially
  
}

void variableUpdate()
{

  notify.notifyWiFiConnected(wifiState, connectedToNetwork); // Notify Wi-Fi connection status
  notify.notifyBLEConnected(bleConnected);    // Notify BLE connection status
  // notify.notifyMqttConnected(wifiMqtt.connected()); // Notify MQTT connection status
  // Store file reads in temporary String variables to prevent multiple calls
  String newDeviceLock = flash.ReadFile(SPIFFS, "/mLock.txt");
  // String newDecoderKey = flash.NVS_ReadString("decoder_key");
  String newDeviceMode = flash.ReadFile(SPIFFS, "/device_mode.txt");
  float newTotalUnit = flash.ReadFile(SPIFFS, "/total_unit.txt").toFloat();
  float newStoredConsumption = flash.ReadFile(SPIFFS, "/storedConsumption.txt").toFloat();


  // Update meterLock if different
  if (strcmp(deviceLock, newDeviceLock.c_str()) != 0)
  {
    deviceLock = strdup(newDeviceLock.c_str()); // Duplicate string
    delay(1);
  }


  // Update totalUnit if different
  if (totalUnit != newTotalUnit)
  {
    totalUnit = newTotalUnit;
    delay(1);
  }


  if (storedConsumption != newStoredConsumption)
  {
    storedConsumption = newStoredConsumption;
    delay(1);
  }

  // if (decoderKey != newDecoderKey)
  // {
  //   decoderKey = newDecoderKey;
  //   delay(1);
  // }

  if (strcmp(deviceMode, newDeviceMode.c_str()) != 0)
  {
    deviceMode = strdup(newDeviceMode.c_str());
    delay(1);
  }
  
}
