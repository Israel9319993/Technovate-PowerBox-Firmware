#include "proccess_manager.h"
#include "mqtt.h"
#include "connectivity.h"
#include "bluetooth.h"
#include "freertos/queue.h"

extern Ble bluetooth;

TaskHandle_t bleTaskHandle = NULL;

// Function to send BLE meter data
void BLEPowerBoxSend(void *declaration)
{
    (void)declaration;

    static unsigned long lastSendTime = 0;
    const int sendDuration = 2000;

    while (true)
    {
        if (millis() - lastSendTime >= sendDuration)
        {
            lastSendTime = millis(); // Update the last send time

            // Prepare JSON document
            JsonDocument doc;

            doc["battVolt"] = bmsVoltage;
            doc["battPercent"] = bmsSOC;
            // doc["cell1"] = cell1;
            // doc["cell2"] = cell2;
            // doc["cell3"] = cell3;
            // doc["cell4"] = cell3;
            doc["balUnit"] = balUnit;
            doc["totalUnit"] = totalUnit;
            doc["battHealth"] = bmsSOH;
            doc["battRCC"] = bmsRCC;
            doc["chargeCycles"] = chargeCycles;
            doc["battFCC"] = bmsFCC;
            doc["battRCC"] = bmsRCC;

            doc["solarVoltage"] = solarVoltage;
            doc["solarCurrent"] = solarCurrent;
            doc["acVolt"] = acVolt;
            doc["power"] = power;
            doc["usage"] = usage;
            doc["powerFactor"] = powerFactor;
            doc["frequency"] = frequency;
            doc["chargeCurrent"] = bmsCurrent;
            doc["state"] = pwrBState;
            doc["mode"] = deviceMode;
            doc["deviceId"] = deviceId;
            doc["deviceState"] = deviceState;
            // Serialize JSON and send via BLE
            String responseOutput;
            serializeJsonPretty(doc, responseOutput);

            Serial.println("BLE send: " + responseOutput);
            pTTxCharacteristic->setValue((uint8_t *)responseOutput.c_str(), responseOutput.length());
            pTTxCharacteristic->notify();
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void processInit()
{

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
}
