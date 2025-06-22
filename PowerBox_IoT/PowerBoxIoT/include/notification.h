#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
// #include <Audio.h>
#include "global_config.h"




// 
class Notification
{
public:
    Notification();
    void Begin();
    void Loop();
    void DisplayNotification(const char* title,const char* subTitle,const char* type);
    void playAudioFromSPIFFS(const char* filePath);
    private:    
  
};

#endif // NOTIFICATION_H


void notificationTask(void *pvParameters);


// // Optional: Audio status callbacks
// void audio_info(const char *info) {
//   Serial.print("info: "); Serial.println(info);
// }

// void audio_id3data(const char *info) { // ID3 metadata
//   Serial.print("id3data: "); Serial.println(info);
// }

// void audio_eof_mp3(const char *info) { // End of file
//   Serial.print("eof_mp3: "); Serial.println(info);
// }

// void audio_showstation(const char *info) {
//   Serial.print("station: "); Serial.println(info);
// }

// void audio_showstreamtitle(const char *info) {
//   Serial.print("streamtitle: "); Serial.println(info);
// }

// void audio_bitrate(const char *info) {
//   Serial.print("bitrate: "); Serial.println(info);
// }