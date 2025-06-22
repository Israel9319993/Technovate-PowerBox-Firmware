#include "flash_mem.h"

Flash::Flash() {}

void Flash::Begin()
{

    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
    {
        Serial.println("SPIFFS Mount Failed");
        //     return;
    }
    preferences.begin("firmware", false); // Use "storage" namespace
    // Serial.println("NVS Initialized");
    // if (NVS_ReadString("device_id") == "")
    // {
    //     NVS_WriteString("device_id", "5100100000000");
    // }
    // if (NVS_ReadString("old_firmware") == "")
    // {
    //     NVS_WriteString("old_firmware", "1.0");
    // }
    // if (NVS_ReadString("new_firmware") == "")
    // {
    //     NVS_WriteString("new_firmware", "1.0");
    // }
    DefaultData();
}

void Flash::DefaultData()
{

    if (ReadFile(SPIFFS, "/total_unit.txt") == 0)
    {
        WriteFile(SPIFFS, "/total_unit.txt", "5");
    }
    delay(1);
    if (ReadFile(SPIFFS, "/wifi_mode.txt") == 0)
    {
        WriteFile(SPIFFS, "/wifi_mode.txt", "on");
    }
    delay(1);

    if (ReadFile(SPIFFS, "/device_mode.txt") == 0)
    {
        WriteFile(SPIFFS, "/device_mode.txt", "prepaid");
    }

    if (ReadFile(SPIFFS, "/ups_mode.txt") == 0)
    {
        WriteFile(SPIFFS, "/ups_mode.txt", "off");
    }
    delay(1);
    if (ReadFile(SPIFFS, "/ble_mode.txt") == 0)
    {
        WriteFile(SPIFFS, "/ble_mode.txt", "off");
    }
    delay(1);
    if (ReadFile(SPIFFS, "/mControl.txt") == 0)
    {
        WriteFile(SPIFFS, "/mControl.txt", "on");
    }
    delay(1);
    if (ReadFile(SPIFFS, "/mLock.txt") == 0)
    {
        WriteFile(SPIFFS, "/mLock.txt", "unlock");
    }
    delay(1);
    if (ReadFile(SPIFFS, "/storedConsumption.txt") == 0)
    {
        WriteFile(SPIFFS, "/storedConsumption.txt", "0");
    }
    delay(1);
    if (ReadFile(SPIFFS, "/ssid.txt") == 0)
    {
        WriteFile(SPIFFS, "/ssid.txt", "ISWLOS_ENGINEERING");
    }
    delay(1);
    if (ReadFile(SPIFFS, "/password.txt") == 0)
    {
        WriteFile(SPIFFS, "/password.txt", "9Q2FQE86(Tge@W9ZHj#tUY#4");
    }
    delay(1);
    if (ReadFile(SPIFFS, "/bckl.txt") == 0)
    {
        WriteFile(SPIFFS, "/bckl.txt", "150");
    }
    bckl = ReadFile(SPIFFS, "/bckl.txt").toInt();
    delay(1);
    totalUnit = ReadFile(SPIFFS, "/total_unit.txt").toFloat();
    delay(1);

    deviceLock = strdup(ReadFile(SPIFFS, "/mLock.txt").c_str());
    delay(1);
    storedConsumption = ReadFile(SPIFFS, "/storedConsumption.txt").toFloat();
    delay(1);
    deviceId = NVS_ReadString("device_id");
    Serial.println("Newdevice ID: " + String(deviceId) + "  real value: " + NVS_ReadString("device_id"));
    delay(1);

    const char *wifiInitState = strdup(ReadFile(SPIFFS, "/wifi_mode.txt").c_str());
    delay(1);
    wifiFlag = strcmp(wifiInitState, "on") == 0 ? true : false;

    const char *bleInitState = strdup(ReadFile(SPIFFS, "/ble_mode.txt").c_str());
    delay(1);
    bleFlag = strcmp(bleInitState, "on") == 0 ? true : false;

    const char *upsInitState = strdup(ReadFile(SPIFFS, "/ups_mode.txt").c_str());
    delay(1);
    upsFlag = strcmp(upsInitState, "on") == 0 ? true : false;
    // oldFirmwareVersion = NVS_ReadString("old_firmware").toFloat();
    // delay(1);
    // newFirmwareVersion = NVS_ReadString("new_firmware").toFloat();
    // delay(1);
    wifiCredentials.ssid = strdup(ReadFile(SPIFFS, "/ssid.txt").c_str());
    delay(1);
    wifiCredentials.password = strdup(ReadFile(SPIFFS, "/password.txt").c_str());
    delay(1);
}

String Flash::ReadFile(fs::FS &fs, const char *path)
{
    // Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path, "r");
    if (!file || file.isDirectory())
    {
        Serial.println("- failed to open file for reading");
        return "";
    }

    size_t fileSize = file.size();
    if (fileSize == 0)
    {
        Serial.println("- file is empty");
        file.close();
        return "";
    }

    String content;
    while (file.available())
    {
        content += (char)file.read();
    }

    file.close();
    return content;
}

void Flash::ListDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels)
            {
                ListDir(fs, file.path(), levels - 1);
            }
        }
        else
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void Flash::WriteFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("- failed to open file for writing");
        return;
    }
    if (file.write((const uint8_t *)message, strlen(message)))
    {
        Serial.println("- file written");
    }
    else
    {
        Serial.println("- write failed");
    }
    file.close();
}

void Flash::AppendFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("- failed to open file for appending");
        return;
    }
    if (file.write((const uint8_t *)message, strlen(message)))
    {
        Serial.println("- message appended");
    }
    else
    {
        Serial.println("- append failed");
    }
    file.close();
}

void Flash::DeleteFile(fs::FS &fs, String path)
{
    Serial.printf("Deleting file: %s\r\n", path);
    if (fs.remove(path))
    {
        Serial.println("- file deleted");
    }
    else
    {
        Serial.println("- delete failed");
    }
}

void Flash::FormatFlash()
{
    bool formatted = SPIFFS.format();

    if (formatted)
    {
        Serial.println("\n\nSuccess formatting");
        // ESP.restart();
    }
    else
    {
        Serial.println("\n\nError formatting");
    }
}

const char *Flash::FormatFloatToString(float value)
{
    char *buffer = (char *)malloc(20 * sizeof(char)); // Dynamically allocate memory for the buffer
    if (buffer)
    {
        sprintf(buffer, "%.2f", value); // Format float to string with 2 decimal places
    }
    return buffer; // Return the allocated buffer
}

// ==== NVS Functions ====
void Flash::NVS_WriteString(const char *key, const String &value)
{
    preferences.putString(key, value);
    Serial.println("Data Written to NVS: " + String(key) + " = " + value);
}

String Flash::NVS_ReadString(const char *key, const String &defaultValue)
{
    String value = preferences.getString(key, defaultValue);
    // Serial.println("Read from NVS: " + String(key) + " = " + value);
    return value;
}

void Flash::NVS_RemoveKey(const char *key)
{
    preferences.remove(key);
    Serial.println("Key Removed from NVS: " + String(key));
}

void Flash::NVS_Clear()
{
    preferences.clear();
    Serial.println("NVS Cleared");
}

void Flash::NVS_Close()
{
    preferences.end();
    Serial.println("NVS Closed");
}
