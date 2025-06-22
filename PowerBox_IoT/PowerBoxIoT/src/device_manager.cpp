#include "device_manager.h"
#include "flash_mem.h"
#include "disp_setup.h"
#include "connectivity.h"
#include "device_setup.h"
#include "task.h"
#include "ui.h"

extern Flash flash;
extern Connection connection;
// Declare the event_handler function
// void event_handler(lv_event_t *e);

// int ini_bckl;

void variableUpdate()
{

  // if (ini_bckl != bckl)
  // {
  //   ini_bckl = bckl;

  //   delay(10);
  // }

  // Update Time
  if (timeOut != nullptr)
  {
    lv_label_set_text(ui_Time, timeOut);
  }

  // Battery Percentage
  char battPercentStr[8];
  snprintf(battPercentStr, sizeof(battPercentStr), "%d", battPercent);
  lv_bar_set_value(ui_batteryGuage, battPercent, LV_ANIM_ON);
  lv_label_set_text(ui_BattPercent, battPercentStr);

  // Battery Voltage (Ignore small changes)
  char battVoltStr[8];
  snprintf(battVoltStr, sizeof(battVoltStr), "%.2f", battVolt);
  lv_label_set_text(ui_battVolt, battVoltStr);

  // Cell Voltages
  char cell1Str[8], cell2Str[8], cell3Str[8];
  snprintf(cell1Str, sizeof(cell1Str), "%.2f", cell1);
  snprintf(cell2Str, sizeof(cell2Str), "%.2f", cell2);
  snprintf(cell3Str, sizeof(cell3Str), "%.2f", cell3);
  lv_label_set_text(ui_cell1, cell1Str);
  lv_label_set_text(ui_cell2, cell2Str);
  lv_label_set_text(ui_cell3, cell3Str);

  // Solar Voltage
  char solarVoltageStr[8];
  snprintf(solarVoltageStr, sizeof(solarVoltageStr), "%.2f", solarVoltage);
  lv_label_set_text(ui_SolarVolt, solarVoltageStr);
  lv_label_set_text(ui_solarVolt, solarVoltageStr);

  // Solar Current
  char solarCurrentStr[8];
  snprintf(solarCurrentStr, sizeof(solarCurrentStr), "%.2f", solarCurrent);
  lv_label_set_text(ui_SolarCurrent, solarCurrentStr);

  // Charge Current
  char chargeCurrentStr[8];
  snprintf(chargeCurrentStr, sizeof(chargeCurrentStr), "%.2f", chargeCurrent);
  lv_label_set_text(ui_chargeCurrent1, chargeCurrentStr);

  // Load Voltage
  char acOutStr[8];
  snprintf(acOutStr, sizeof(acOutStr), "%.2f", acVolt);
  lv_label_set_text(ui_LoadVolt, acOutStr);

  // char acOutStr2[8];
  // snprintf(acOutStr2, sizeof(acOutStr), "%.2f", acOut);
  lv_label_set_text(ui_gridVolt, (digitalRead(nepaPin) == HIGH) ? acOutStr : "0.00");

  // Load Power
  char pwrStr[8];
  snprintf(pwrStr, sizeof(pwrStr), "%.2f", pwr);
  lv_label_set_text(ui_loadPwr, pwrStr);

  // Balance Unit
  char balUnitStr[8];
  snprintf(balUnitStr, sizeof(balUnitStr), "%.3f", balUnit);
  lv_label_set_text(ui_BalUnit, balUnitStr);
  lv_label_set_text(ui_totalUsage1, balUnitStr);

  // Total Unit
  char totalUnitStr[8];
  snprintf(totalUnitStr, sizeof(totalUnitStr), "%.3f", totalUnit);
  lv_label_set_text(ui_totalUnit, totalUnitStr);

  // Usage
  char usageStr[8];
  snprintf(usageStr, sizeof(usageStr), "%.3f", usage);
  lv_label_set_text(ui_totalUsage, usageStr);



  if (wifiScan == true)
  {

    xTaskCreate(wifiScanTask, "WiFiScan", 4096, NULL, 1, NULL);

    wifiScan = false;

  }
}

unsigned long powerLossTime = 0;
const unsigned long debounceDelay = 500;



void deviceOperation()
{
  lv_event_t *e = nullptr;



  if (strcmp(deviceMode, "prepaid") == 0)
  {
    balUnit = totalUnit - usage;
  }
  else
  {
    balUnit = 0;
    totalUnit = 0;
  }
  



  if (balUnit <= 0)
  {
    power_OFF(e);
    lv_obj_remove_state(ui_pwrBtn, LV_STATE_CHECKED);
  }

  if (strcmp(deviceLock, "unlock") == 0)
  {
    if (deviceControl == "on" && state == 0)
    {
      power_ON(e);
      lv_obj_add_state(ui_pwrBtn, LV_STATE_CHECKED);
      deviceControl = "";
    }

    if (deviceControl == "off" && state == 1)
    {
      power_OFF(e);
      lv_obj_remove_state(ui_pwrBtn, LV_STATE_CHECKED);
      deviceControl = "";
    }
  }
  else
  {
    power_OFF(e);
    lv_obj_remove_state(ui_pwrBtn, LV_STATE_CHECKED);
    deviceControl = "";
  }

  if (wifiFlag == true)
  {
    lv_obj_add_state(ui_wifiSwitch, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_remove_state(ui_wifiSwitch, LV_STATE_CHECKED);
  }

  if (upsFlag == true)
  {
    lv_obj_add_state(ui_upsSwitch, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_remove_state(ui_upsSwitch, LV_STATE_CHECKED);
  }

  if (bleFlag == true)
  {
    lv_obj_add_state(ui_bluetoothSwitch1, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_remove_state(ui_bluetoothSwitch1, LV_STATE_CHECKED);
  }

  if (pwrCount == 0 && digitalRead(nepaPin) == HIGH)
  {
    pwrCount = 1; // Set power count when mains power is available
  }
  else if (pwrCount == 1 && digitalRead(nepaPin) == LOW)
  {
    // Start debounce timer when power loss is detected
    if (powerLossTime == 0)
    {
      powerLossTime = millis();
    }
    // Confirm power loss after debounce delay
    if (millis() - powerLossTime > debounceDelay)
    {
      pwrCount = 2;
      powerLossTime = 0; // Reset timer
    }
  }
  else
  {
    powerLossTime = 0; // Reset timer if power is restored
  }

  // UPS switching logic
  if (upsFlag && state == 0 && digitalRead(nepaPin) == LOW && pwrCount == 2)
  {
    power_ON(e);
    lv_obj_add_state(ui_pwrBtn, LV_STATE_CHECKED);
    pwrCount = 0; // Reset when power returns
  }

  if(digitalRead(nepaPin) == HIGH  && state == 1){
    power_OFF(e);
    lv_obj_remove_state(ui_pwrBtn, LV_STATE_CHECKED);
    pwrCount = 0; // Reset when power returns
  }

  // Reset when mains power is restored
  if (pwrCount == 2 && digitalRead(nepaPin) == HIGH)
  {
    pwrCount = 1;
  }
 
  

  if(digitalRead(nepaPin) == HIGH){

    deviceState = "charging";

  }
  else if(digitalRead(nepaPin) == LOW && state == 1){

    deviceState = "discharging";
  }

  else if(digitalRead(nepaPin) == LOW && state == 0){

    deviceState = "idle";
  }
    


  if (strcmp(deviceLock, "unlock") == 0) {
    // if (digitalRead(nepaPin) == LOW ) {
       pwrBState = (state == 1) ? "on" : "off";
    // }
    // else {
    //    pwrBState = "charging";
    // }

} 

else {
   pwrBState = "lock";
}




// /   if (pwrCount == 0 && digitalRead(nepaPin) == HIGH ) {
  //     pwrCount = 1;  // Set power count when mains power is available
  // }
  // else if (pwrCount == 1 && digitalRead(nepaPin) == LOW ) {
  //     pwrCount = 2;  // Detect power loss
  // }
  // else if (pwrCount == 2 && digitalRead(nepaPin) == HIGH ) {
  //     pwrCount = 1;  // Reset when power returns
  // }

  // // UPS switching logic
  // if (upsFlag && state == 0 && digitalRead(nepaPin) == LOW && pwrCount == 2) {
  //     power_ON(e);
  //     lv_obj_add_state(ui_pwrBtn, LV_STATE_CHECKED);
  //     pwrCount = 1;  // Reset when power returns
  // }

  // }

  

  _ui_flag_modify(ui_gridActive, LV_OBJ_FLAG_HIDDEN, (digitalRead(nepaPin) == HIGH) ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_solarActive, LV_OBJ_FLAG_HIDDEN, (solarVoltage > 6) ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_wifiIcon, LV_OBJ_FLAG_HIDDEN, (wifiState && wifiFlag) ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_bluetoothicon, LV_OBJ_FLAG_HIDDEN, (bleConnected) ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_liteIcon, LV_OBJ_FLAG_HIDDEN, (connectedToNetwork) ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_upsIcon, LV_OBJ_FLAG_HIDDEN, (upsFlag) ? _UI_MODIFY_FLAG_REMOVE : _UI_MODIFY_FLAG_ADD);
}
