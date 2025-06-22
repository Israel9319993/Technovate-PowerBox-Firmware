#include "task.h"
#include "mqtt.h"
#include "flash_mem.h"
#include "time_lib.h"
#include "device_manager.h"
#include "notification.h"
#include "energy_module.h"
#include "bluetooth.h"
extern EnergySensor readPzem;

Notification notification;

#include "connectivity.h"
extern Connection connection;
extern Flash flash;
extern Time serverTime;

//  int ini_bckl;
unsigned long lastWriteTime = 0;
const unsigned long writeInterval = 500;
TaskHandle_t readTaskHandle = NULL;
TaskHandle_t uiTaskHandle = NULL;
const float maxVoltage = 12.6; // Max voltage of fully charged battery
const float minVoltage = 10.5; // Min voltage for empty battery
static char prevTime[20] = "";

extern Ble bluetooth;
TaskHandle_t bleTaskHandle = NULL;




void readEnergyTask(void *pvParameters)
{

  (void)pvParameters;

  while (true)
  {
    if(acVolt != readPzem.GetVoltage()) {
      acVolt = readPzem.GetVoltage();
    }
    // if(current != 0.0 && current != readPzem.GetCurrent()) {
    //   current = readPzem.GetCurrent();
    // }
    if(pwr != readPzem.GetPower()) {
      pwr = readPzem.GetPower();
    }
    // if(freq != 0.0 && freq != readPzem.GetFrequency()) {
    //   freq = readPzem.GetFrequency();
    // }
    if(usage != readPzem.GetEnergy()) {
      usage = readPzem.GetEnergy();
    }
    if(frequency != readPzem.GetFrequency()) {
      frequency = readPzem.GetFrequency();
    }
    if(powerFactor != readPzem.GetPowerFactor()) {
      powerFactor = readPzem.GetPowerFactor();
    }
    // if(pF != 0.0 && pF != readPzem.GetPowerFactor()) {
    //   pF = readPzem.GetPowerFactor();
    // }
    // // float current = readPzem.GetCurrent();
    // pwr = readPzem.GetPower();
    // // float freq = readPzem.GetFrequency();
    // usage = readPzem.GetEnergy();
    // // float pF = readPzem.GetPowerFactor();

    Serial.print("Voltage: ");
    Serial.println(acVolt);

    Serial.print("Power: ");
    Serial.println(pwr);

 
    Serial.print("Energy Consumption: ");
    Serial.println(usage);
    
   
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Delay for a while
  }
}


void readTask(void *pvParameters)
{

  String data = "";
  serverTime.Begin();

  while (true)
  {
    if (Serial.available() > 0)
    {
      while (Serial.available() > 0)
      {
        char c = Serial.read();
        data += c;
        vTaskDelay(1);
      }
      serverTime.ReadTime();
      float percentage = map(battVolt * 100, minVoltage * 100, maxVoltage * 100, 0, 100); // Scale to 0-100%
      percentage = constrain(percentage, 0, 100);                                         // Ensure percentage is within 0-100%
  
      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, data);
      if (!error)
      {
        battVolt = doc["v"];
        cell1 = doc["c1"];
        cell2 = doc["c2"];
        cell3 = doc["c3"];
        usage = readPzem.GetEnergy();
        battPercent = percentage;
        solarVoltage = doc["sv"];
        solarCurrent = (solarVoltage > 6) ? doc["c"] : 0.00;
        chargeCurrent = doc["c"];
      }

      data = "";
    }
    // voltage = readPzem.GetVoltage();
    // current = readPzem.GetCurrent();
    // power = readPzem.GetPower();
    // freq = readPzem.GetFrequency();
    // energyConsumption = readPzem.GetEnergy();
    // pF = readPzem.GetPowerFactor();
    // variableUpdate();
    // deviceOperation();
    // battVolt = random(0,100); // Random voltage between 10.5 and 12.6
    // battPercent = percentage;
    // cell1 = random(0,4);        // Random cell voltage between 3.5 and 4.2
    // cell2 = random(0,4);        // Random cell voltage between 3.5 and 4.2
    // cell3 = random(0,4);        // Random cell voltage between 3.5 and 4.2
    // usage = random(0,5);               // Random usage between 0 and 100
    // solarVoltage = random(0, 200) / 10.0; // Random solar voltage between 0 and 20.0
    // solarCurrent = random(0, 100) / 10.0; // Random solar current between 0 and 10.0
    // acVolt = random(220, 240);            // Random AC voltage between 220 and 240
    // acOut = random(220, 240);             // Random AC output voltage between 220 and 240
    // pwr = random(0, 1000);                // Random power between 0 and 1000
    // chargeCurrent = doc["c"];

    // if (data != "")
    // {
    //   data = "";
    // }

    // balUnit = totalUnit - usage;

    String newDeviceLock = flash.ReadFile(SPIFFS, "/mLock.txt");
    // String newDeviceControl = flash.ReadFile(SPIFFS, "/mControl.txt");
    String newWifiFlag = flash.ReadFile(SPIFFS, "/wifi_mode.txt");
    bool newWifiInit = (newWifiFlag == "on") ? true : false;

    String newUpsFlag = flash.ReadFile(SPIFFS, "/ups_mode.txt");
    bool newUpsInit = (newUpsFlag == "on") ? true : false;
    String newDeviceMode = flash.ReadFile(SPIFFS, "/device_mode.txt");
    String newBleFlag = flash.ReadFile(SPIFFS, "/ble_mode.txt");
    bool newBleInit = (newBleFlag == "on") ? true : false;
    float newTotalUnit = flash.ReadFile(SPIFFS, "/total_unit.txt").toFloat();
    float newStoredConsumption = flash.ReadFile(SPIFFS, "/storedConsumption.txt").toFloat();
    float newBckl = flash.ReadFile(SPIFFS, "/bckl.txt").toInt();
    std::string newSsid = flash.ReadFile(SPIFFS, "/ssid.txt").c_str();
    std::string newPassword = flash.ReadFile(SPIFFS, "/password.txt").c_str();

    // Update DeviceLock if different
    if (strcmp(deviceLock, newDeviceLock.c_str()) != 0)
    {
      free((void *)deviceLock);                   // Free the previously allocated memory
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
    // Update WiFi flag if different
    if (wifiFlag != newWifiInit)
    {
      wifiFlag = newWifiInit; // Update flag
    }

    // Update UPS flag if different
    if (upsFlag != newUpsInit)
    {
      upsFlag = newUpsInit; // Update flag
    }

    // Update BLE flag if different
    if (bleFlag != newBleInit)
    {
      bleFlag = newBleInit; // Update flag
    }

    if (newBckl != bckl)
    {
      // lv_slider_set_value(ui_BackLight,bckl, LV_ANIM_OFF);
      newBckl = bckl;
      flash.WriteFile(SPIFFS, "/bckl.txt", String(bckl).c_str());
    }

    if (strcmp(wifiCredentials.ssid, newSsid.c_str()) != 0)
    {
      wifiCredentials.ssid = newSsid.c_str();
    }
    if (strcmp(wifiCredentials.password, newPassword.c_str()) != 0)
    {
      wifiCredentials.password = newPassword.c_str();
    }


    if (strcmp(deviceMode, newDeviceMode.c_str()) != 0)
    {
      deviceMode = strdup(newDeviceMode.c_str());
      delay(1);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Delay for a while
  }
}

void scan_wifi_task(void *pvParameters)
{
  lv_dropdown_set_text(ui_WifiList, "Scanning...");
  _ui_flag_modify(ui_wifiLoading, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  _ui_flag_modify(ui_WifiList, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

  // Ensure Wi-Fi is disconnected before scanning
  WiFi.disconnect(true);
  vTaskDelay(pdMS_TO_TICKS(500)); // Small delay to ensure disconnection

  int n = WiFi.scanNetworks();
  Serial.println("Scan done");

  if (n == -1)
  {
    Serial.println("Wi-Fi scan failed");
    lv_dropdown_set_text(ui_WifiList, "Scan failed");
  }
  else if (n == 0)
  {
    Serial.println("No networks found");
    lv_dropdown_set_text(ui_WifiList, "No networks found");
  }
  else
  {
    Serial.printf("%d networks found:\n", n);
    std::string list = ""; // Using std::string for better memory management

    for (int i = 0; i < n; ++i)
    {
      list += WiFi.SSID(i).c_str();
      list += "\n";
    }

    Serial.println(list.c_str());
    lv_dropdown_set_text(ui_WifiList, "Select a Network:");
    lv_dropdown_set_options(ui_WifiList, list.c_str());
    lv_dropdown_open(ui_WifiList);
  }

  // Free memory used by scan results
  WiFi.scanDelete();

  // Hide loading icon
  _ui_flag_modify(ui_wifiLoading, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

  // Ensure event handlers are correctly set
  lv_obj_add_event_cb(ui_WifiList, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_keyboard, ui_event_keyboard, LV_EVENT_ALL, NULL);

  // Mark scan as complete
  wifiScan = false;

  // Delete the task properly
  vTaskDelete(NULL);
}

void connect_wifi_task(void *pvParameters)
{
  WiFi.begin(newSsid.c_str(), newPassword.c_str());
  Serial.println("Connecting :" + String(newSsid) + "  password: " + String(newPassword));
  int count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");

    lv_dropdown_set_text(ui_WifiList, "Connecting.....");
    count++;
    if (count > 20)
    {
      break;
    }
  }
  _ui_flag_modify(ui_wifiLoading, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  if (WiFi.status() == WL_CONNECTED)
  {
    flash.WriteFile(SPIFFS, "/ssid.txt", newSsid.c_str());
    delay(100);
    flash.WriteFile(SPIFFS, "/password.txt", newPassword.c_str());
    delay(100);
    lv_dropdown_set_text(ui_WifiList, "WiFi Connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(1000);
    lv_dropdown_set_text(ui_WifiList, "WiFi Connected");
    delay(1000);
    // _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen1_screen_init);
    // xTaskCreatePinnedToCore(getNtpTime, "getNtpTime", 4096, NULL, 1, NULL, 1);
    // xTaskCreatePinnedToCore(getWeather, "getWeather", 4096, NULL, 1, NULL, 1);
  }
  else
  {
    Serial.println("WiFi connect failed");
    lv_dropdown_set_text(ui_WifiList, "WiFi connect failed");
    delay(1000);
    // lv_label_set_text(ui_Label12, "请连接WiFi");
    // lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_HIDDEN);
  }
  vTaskDelete(NULL);
}

void pushMsg(void *pvParameters)
{

  (void)pvParameters;

  delay(10000);

  while (true)
  {

    if (wifiState && wifiFlag)
    {
      Serial.println("wifi runing here");
      mqttConnect(wifiMqtt);
    }

    // delay(100);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void wifiScanTask(void *param)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();               // Ensure clean state
  vTaskDelay(pdMS_TO_TICKS(1000)); // Allow mode change to take effect
  WiFi.scanNetworks(true);         // Start scanning in async mode
  Serial.println("Scanning...");
  lv_dropdown_set_text(ui_WifiList, "Scanning...");
  _ui_flag_modify(ui_WifiList, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  _ui_flag_modify(ui_wifiLoading, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

  while (WiFi.scanComplete() == -1)
  {
    Serial.println("Scanning...");
    vTaskDelay(pdMS_TO_TICKS(500)); // Yield CPU to avoid watchdog reset
  }

  int n = WiFi.scanComplete();
  // Hide loading icon
  _ui_flag_modify(ui_wifiLoading, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  if (n == -2)
  {
    Serial.println("Wi-Fi scan failed");
    if (ui_WifiList)
    {
      lv_dropdown_set_text(ui_WifiList, "Scan failed");
    }
  }
  else if (n == 0)
  {
    Serial.println("No networks found");
    if (ui_WifiList)
    {
      lv_dropdown_set_text(ui_WifiList, "No networks found");
    }
  }
  else
  {
    Serial.printf("Scan complete: %d networks found\n", n);
    String list = ""; // Use String instead of std::string

    for (int i = 0; i < n; ++i)
    {
      list += WiFi.SSID(i);
      list += "\n";
    }

    Serial.println(list);

    lv_dropdown_set_text(ui_WifiList, "Select a Network:");
    lv_dropdown_set_options(ui_WifiList, list.c_str());
    lv_dropdown_open(ui_WifiList);
  }

  // Hide loading UI safely
  _ui_flag_modify(ui_wifiLoading, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  // // Free memory used by scan results
  WiFi.scanDelete();

  // Ensure UI event handlers are properly set
  if (ui_WifiList)
    lv_obj_add_event_cb(ui_WifiList, event_handler, LV_EVENT_ALL, NULL);
  if (ui_keyboard)
    lv_obj_add_event_cb(ui_keyboard, ui_event_keyboard, LV_EVENT_ALL, NULL);

  // Mark scan as complete
  vTaskDelete(NULL); // Delete task to free memory
}


void BLEPowerBoxSend(void *declaration)
{
    (void)declaration;

    static unsigned long lastSendTime = 0;
    const int sendDuration = 4000;

    while (true)
    {
        if (millis() - lastSendTime >= sendDuration)
        {
            lastSendTime = millis(); // Update the last send time

            // Prepare JSON document
            JsonDocument doc;

            doc["battVolt"] = battVolt;
            doc["battPercent"] = battPercent;
            doc["cell1"] = cell1;
            doc["cell2"] = cell2;
            doc["cell3"] = cell3;
            doc["cell4"] = cell3;
            doc["balUnit"] = balUnit;
            doc["totalUnit"] = totalUnit;

            doc["battHealth"] =  battPercent;  // bmsSOH;
            doc["battRCC"] =   100;     //bmsRCC;
            doc["chargeCycles"] =  0; //chargeCycles;
            doc["battFCC"] =   100;    //bmsFCC;
    
            doc["solarVoltage"] = solarVoltage;
            doc["solarCurrent"] = solarCurrent;
            doc["acVolt"] = acVolt;
            doc["power"] = pwr;
            doc["usage"] = usage;
            doc["powerFactor"] = powerFactor;
            doc["frequency"] = frequency;
            doc["chargeCurrent"] =  chargeCurrent;
            doc["state"] = pwrBState;
            doc["upsFlag"] = upsFlag;
            doc["mode"] = deviceMode;
            doc["deviceId"] = deviceId;
            doc["deviceState"] = deviceState;
            // Serialize JSON and send via BLE
            String responseOutput;
            serializeJson(doc, responseOutput);

            Serial.println("BLE send: " + responseOutput);
            pTTxCharacteristic->setValue((uint8_t *)responseOutput.c_str(), responseOutput.length());
            pTTxCharacteristic->notify();
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

// void BLEPowerBoxConnect(void *declaration)
// {
//   (void)declaration;
//   Serial.println("BLEPowerBoxConnect Task Started");

//   if (deviceId.length() == 0) {
//     Serial.println("ERROR: deviceId is empty!");
//     vTaskDelete(NULL);
//     return;
//   }

//   Serial.println("Calling bluetooth.Begin()");
//   bluetooth.Begin(deviceId.c_str());
//   Serial.println("bluetooth.Begin() completed");

//   BaseType_t result = xTaskCreatePinnedToCore(
//     BLEPowerBoxSend,
//     "BLEMeterSend",
//     4096,
//     NULL,
//     1,
//     &bleTaskHandle,
//     0);

//   if (result == pdPASS && bleTaskHandle != NULL)
//   {
//     Serial.println("BLEPowerBoxSend task created, now suspending...");
//     vTaskSuspend(bleTaskHandle);
//   }
//   else {
//     Serial.println("Failed to create BLEPowerBoxSend task.");
//   }

//   vTaskDelete(NULL);  // End this task after setup
// }

