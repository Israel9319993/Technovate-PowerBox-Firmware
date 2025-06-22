#include "ui.h"
#include <Arduino.h>
#include "global.h"

#include <WiFi.h>
#include "flash_mem.h"

extern Flash flash;

// const char* ssid = "your_ssid";    // Replace with your SSID
// const char* password = "your_password"; // Replace with your password

// Function to handle power ON
void power_ON(lv_event_t * e) {
    if(state == 0){
    btn_Animation(ui_SwitchContainer, 0);
	_ui_state_modify(ui_pbx, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
	_ui_flag_modify(ui_inverterActive, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    _ui_image_set_property(ui_load, _UI_IMAGE_PROPERTY_IMAGE, (uint8_t*)&ui_img_628039206);
    digitalWrite(relay, HIGH);
    state = 1;
    }
}

// Function to handle power OFF
void power_OFF(lv_event_t * e) {
       if(state == 1){
    btn_Animation(ui_SwitchContainer, 0);
    _ui_state_modify(ui_pbx, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_image_set_property(ui_load, _UI_IMAGE_PROPERTY_IMAGE, (uint8_t*)&ui_img_628040357);
        _ui_flag_modify(ui_inverterActive, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    digitalWrite(relay, LOW);
    state = 0;
       }
}

// Function to scan for Wi-Fi networks
void wifiSCAN(lv_event_t * e) {

 wifiFlag = true;
//  lv_dropdown_set_text(ui_WifiList, "Scanning.....");
}

// Function to connect to a selected Wi-Fi network
void wifiSELECT(lv_event_t * e) {

     lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = (lv_obj_t *)lv_event_get_target(e);
    lv_dropdown_set_text(ui_WifiList, "Scan Complete");
  
  
//     WiFi.begin(ssid, password);
//     Serial.print("Connecting to ");
//     Serial.print(ssid);

//     while (WiFi.status() != WL_CONNECTED) {
//         delay(1000);
//         Serial.print(".");
//     }
//     Serial.println();
//     Serial.println("Connected to WiFi");
}

// Function to enable Wi-Fi
void wifiON(lv_event_t * e) {
    // wifiFlag = true;
	flash.WriteFile(SPIFFS, "/wifi_mode.txt", "on");
	// Connect to Wi-Fi
  
//     _ui_flag_modify(ui_wifiIcon, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}

// Function to disable Wi-Fi
void wifiOFFF(lv_event_t * e) {
    // wifiFlag = false;
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
	flash.WriteFile(SPIFFS, "/wifi_mode.txt", "off");
//     _ui_flag_modify(ui_wifiIcon, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}

// Function to handle BLE ON (if needed)
void bleON(lv_event_t * e) {
    // Your code here
	flash.WriteFile(SPIFFS, "/ble_mode.txt", "on");
}

// Function to handle BLE OFF (if needed)
void bleOFF(lv_event_t * e) {
    // Your code here
	flash.WriteFile(SPIFFS, "/ble_mode.txt", "off");
}


// Function to handle BLE ON (if needed)
void upsON(lv_event_t * e) {
    // Your code here
	flash.WriteFile(SPIFFS, "/ups_mode.txt", "on");
}

// Function to handle BLE OFF (if needed)
void upsOFF(lv_event_t * e) {
    // Your code here
	flash.WriteFile(SPIFFS, "/ups_mode.txt", "off");			
}
// Function to display Wi-Fi password details (if needed)
void wifiPasswordDetails(lv_event_t * e) {
    // Your code here
}

// Function to handle backlight events


void ui_BackLight_event_cb(lv_event_t * e) {
    lv_obj_t * slider = (lv_obj_t *)lv_event_get_target(e);
    if( (int)lv_slider_get_value(slider) >= 50){
    ledcWrite(0, (int)lv_slider_get_value(slider));
    bckl = (int)lv_slider_get_value(slider);
    }
}

