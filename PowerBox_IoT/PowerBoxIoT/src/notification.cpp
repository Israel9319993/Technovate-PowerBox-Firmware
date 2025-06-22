#include "notification.h"
#include "ui.h"
#include "global_config.h"
#include "buzzer_alert.h"


extern Buzzer buzzerAlert;
Notification::Notification() {}
// extern QueueHandle_t xQueueAudio;
void Notification::Begin()
{
    // // Initialize Audio
    // // audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    // // audio.setVolume(21);
    //        // Speech
    //        audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT, -1);
    //        audio.setVolume(21);
}
void Notification::DisplayNotification(const char* title, const char* subTitle, const char* type)
{
    // buzzerAlert.PlaySuccess(); 

    if (strcmp(type, "warning") == 0)
    {
        // playAudioFromSPIFFS("/notification/alert.mp3");    

        lv_timer_handler(); // Ensure LVGL updates before transition
        // lv_delay(500);      // Add delay before switching screens

        _ui_screen_change(&ui_Error_Screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 1000, &ui_Error_Screen_screen_init);
        lv_label_set_text(ui_firstErrorLabel, title);
        lv_label_set_text(ui_secondErrorLabel, subTitle); 
    }
    else if (strcmp(type, "success") == 0)
    {
        // buzzerAlert.PlaySuccess(); 
        
        lv_timer_handler(); // Ensure LVGL updates before transition
        // lv_delay(500);      // Add delay before switching screens

        _ui_screen_change(&ui_Success_Screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 1000, &ui_Success_Screen_screen_init);
        lv_label_set_text(ui_firstSuccessLabel, title);
        lv_label_set_text(ui_secondSuccessLabel, subTitle);
    }
}





// void Notification::DisplayNotification(const char* title, const char* subTitle, const char* type) {
//     _ui_screen_change(&ui_Success_Screen, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_Success_Screen_screen_init);
//     lv_label_set_text(ui_firstSuccessLabel, title);
//     lv_label_set_text(ui_secondSuccessLabel, subTitle);

//     if (strcmp(type, "alert") == 0) {
//         playAudioFromSPIFFS("/notification/alert.mp3");
//     }
// }

// void Notification::playAudioFromSPIFFS(const char* filePath) {
//     if (xQueueAudio != NULL) {
//         xQueueSend(xQueueAudio, &filePath, portMAX_DELAY); // Send file path to the queue
//     } else {
//         Serial.println("Error: xQueueAudio is not initialized!");
//     }
// }


