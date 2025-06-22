
#include "disp_setup.h"
#include "global_config.h"
#include "time_lib.h"
#include "task.h"
#include "flash_mem.h"
#include "mqtt.h"
#include "connectivity.h"
#include "device_manager.h"
#include "energy_module.h"
#include "buzzer_alert.h"
#include "bluetooth.h"
EnergySensor readPzem(42,47);

Buzzer buzzerAlert;
Connection connection;
Flash flash;
Time serverTime;
/* Change to your screen resolution */
Ble bluetooth;
// LovyanGFX instance


/*Set tick routine needed for LVGL internal timings*/
static uint32_t my_tick_get_cb(void) { return millis(); }
// SemaphoreHandle_t gui_mutex;

void setup()
{

    Serial.begin(115200);
    // Serial.println("LVGL Widgets Demo");
    pinMode(nepaPin, INPUT);
    //************************FLASH MEMORY INITIALIZATION ******************** */
    flash.Begin();
    //************************************************************************* */

   

    connection.WifiBegin(wifiCredentials.ssid, wifiCredentials.password); // Connect to Wi-Fi
    setupMQTT(wifiMqtt);

    // sntp_set_time_sync_notification_cb(timeavailable);

    // sntp_servermode_dhcp(1); // (optional)
    // configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
    // configTzTime(time_zone, ntpServer1, ntpServer2);
    bluetooth.Begin(deviceId.c_str());

    lv_init();

    ledcSetup(0, 600, 8);
    ledcAttachPin(BCKL, 0);

    ledcWrite(0, bckl);

    // xSemaphore = xSemaphoreCreateBinary();
    // Initially give the semaphore so one task can take it first
    //   xSemaphoreGive(xSemaphore);
    xTaskCreatePinnedToCore(
        pushMsg,
        "pushMsg",
        1024 * 4,
        NULL,
        1,
        NULL,
        1);

    xTaskCreatePinnedToCore(
        readTask,
        "reading",
        1024 * 3,
        NULL,
        1,
        NULL,
        1);

        xTaskCreatePinnedToCore(
          readEnergyTask,
            "readEnergyTask",
            1024 * 3,
            NULL,   
            1,
            NULL,
            1);

            xTaskCreatePinnedToCore(
                BLEPowerBoxSend,
                "BLEMeterSend",
                4096,
                NULL,
                1,
                &bleTaskHandle,
                0);
        
            if (bleTaskHandle != NULL)
            {
                vTaskSuspend(bleTaskHandle);
            }

        // vTaskSuspend(NULL);
    // xTaskCreatePinnedToCore(
    //     notificationTask,
    //     "notificationTask",
    //     1024 * 3,
    //     NULL,
    //     2,
    //     NULL,
    //     1);
    //
    pinMode(relay, OUTPUT);
    //   digitalWrite(38,HIGH);
    // Initialize display
    display.init();
    display.setRotation(0); // Set orientation if needed
    display.fillScreen(TFT_WHITE);
    static lv_disp_t *disp;
    disp = lv_display_create(screenWidth, screenHeight);
    lv_display_set_buffers(disp, buf, NULL, SCREENBUFFER_SIZE_PIXELS * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, my_disp_flush);

    static lv_indev_t *indev;
    indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touchpad_read);

    lv_tick_set_cb(my_tick_get_cb);

    ui_init();

    Serial.println("Setup done");
    // ini_bckl = bckl;
    // buzzerAlert.PlayIntro();
}

void loop()
{
    lv_task_handler();
    // lv_timer_handler(); /* let the GUI do its work */
    lv_timer_handler();
    variableUpdate();
    deviceOperation();
  
    // vTaskResume(NULL);
    // lv_obj_add_event_cb(ui_wifiSwitch, ui_event_wifiSwitch, LV_EVENT_VALUE_CHANGED, NULL);

    vTaskDelay(1); // together with LV_INDEV_DEF_READ_PERIOD it should be bigger than LV_DISP_DEF_REFR_PERIOD, to avoid button-press glitches (e.g. in Smart Gadget example)
}
