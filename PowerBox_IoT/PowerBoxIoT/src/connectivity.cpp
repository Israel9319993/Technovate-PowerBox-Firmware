#include "connectivity.h"
#include "task.h"
#include "flash_mem.h"
#include "device_setup.h"

extern Flash flash;

Connection::Connection() {}

void Connection::WifiBegin(const char *ssid, const char *password)
{
    if (wifiFlag == true)
    {
        _ssid = ssid;
        _password = password;
        WiFi.mode(WIFI_STA);
        WiFi.begin(_ssid, _password);
        // while (WiFi.status() != WL_CONNECTED) {
        //     delay(100);
        //     Serial.print(".");
        // }
        Serial.println("");
        Serial.println("WiFi connected to: " + String(_ssid));
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        // Bind instance methods using lambdas
        WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info)
                     { this->WiFiStationConnected(event, info); }, ARDUINO_EVENT_WIFI_STA_CONNECTED);

        // WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info)
        //              { this->WiFiStationDisconnected(event, info); }, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
    }

    else
    {
        wifiState = false;
    }
}

void Connection::WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    wifiState = true;
    Serial.println("Connected to AP successfully!");
}

void Connection::WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{

    if (wifiFlag == true)
    {
        wifiState = false;
        Serial.println("Disconnected from AP, trying to reconnect...");
        WiFi.begin(wifiCredentials.ssid, wifiCredentials.password); // Attempt reconnection
        connectedToNetwork = false;
    }
    else
    {
        wifiState = false;
    }
}



void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(ui_WifiList, buf, sizeof(buf));
        // LV_LOG_USER("Option: %s", buf);
        newSsid = String(buf);
        Serial.println("Selected SSID: " + String(buf));
       
      
    }
}



void ui_event_keyboard(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // lv_obj_t * target = lv_event_get_target(e);
    static String input; // Static variable to retain the input across events

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        // Get the text area associated with the keyboard
        lv_obj_t * text_area = lv_keyboard_get_textarea(ui_keyboard);
     
        if (text_area == nullptr) {
            Serial.println("Text area is null!");
            return;
        }
        // Get the current text from the text area
        const char * text = lv_textarea_get_text(text_area);

        // Store the entire text in the input string
        // strcpy(input, text);    
        input = String(text);
    }

    if(event_code == LV_EVENT_READY) {
        // Handle when the user finishes entering the text
        wifiPasswordDetails(e);
        _ui_flag_modify(ui_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_PassWordText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

        // Print the total input from the keyboard
      
      newPassword = input;
      Serial.println("Entered Password is : " + newPassword);
    // Clear the input string for the next input session
        //   xTaskCreatePinnedToCore(connect_wifi_task, "connect_wifi_task", 1023*3, NULL, 1, NULL, 0);


        
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
        // input = "";
        // keyFlag = false;
    }
}

