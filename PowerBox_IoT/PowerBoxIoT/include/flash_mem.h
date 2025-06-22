#ifndef FLASH_MEM_H
#define FLASH_MEM_H
#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#include "device_setup.h"
#include "global_config.h"

#include <Preferences.h>
#define FORMAT_SPIFFS_IF_FAILED true

class Flash{

public:
    Flash();
    void Begin();
    void ListDir(fs::FS &fs, const char *dirname, uint8_t levels);
    String ReadFile(fs::FS &fs, const char *path);
    void WriteFile(fs::FS &fs, const char *path, const char *message);
    void AppendFile(fs::FS &fs, const char *path, const char *message);
    void DeleteFile(fs::FS &fs, String path);
    void FormatFlash();
    const char * FormatFloatToString(float value);


 // NVS Functions
    void NVS_WriteString(const char *key, const String &value);
    String NVS_ReadString(const char *key, const String &defaultValue = "");
    void NVS_RemoveKey(const char *key);
    void NVS_Clear();
    void NVS_Close();

    private:
    Preferences preferences;
    void DefaultData();
};

#endif
