#include "mqtt.h"
#include "flash_memory.h"
#include "task.h"
#include "energy_module.h"
#include "buzzer_alert.h"

extern EnergySensor readPzem;
extern Flash flash;
extern Buzzer buzzerAlert;

unsigned long lastStatusTime = 0;
const unsigned long statusInterval = 30000; // 60 seconds

void setupMQTT(PubSubClient &client)
{
    client.setServer(mqttServer, port);
    client.setCallback([&client](char *topic, byte *payload, unsigned int length)
                       { callback(client, topic, payload, length); });

    client.setBufferSize(6000);
}

String pushMessage()
{
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

    String output;
    serializeJsonPretty(doc, output);
    return output;
}

void mqttConnect(PubSubClient &client)
{
    static unsigned long lastReconnectAttempt = 0;

    if (!client.connected())
    {
        unsigned long now = millis();
        if (now - lastReconnectAttempt > 5000)
        {
            lastReconnectAttempt = now;
            reconnect(client);
        }
    }
    else
    {
        client.loop();
        connectedToNetwork = true;

        if (millis() - lastUploadedTime > postingInterval)
        {
            String message = pushMessage();
            publishMessage(client, (String(mqttConfig.publishTopic) + deviceId).c_str(), message.c_str());
            vTaskDelay(10);
            lastUploadedTime = millis();
        }

        if (newFirmwareVersion != oldFirmwareVersion)
        {
            sendResponse(client, (newFirmwareVersion > oldFirmwareVersion) ? (String("ota") + " upgrade").c_str() : (String("ota") + " downgrade").c_str(), "successful", deviceId.c_str());
            oldFirmwareVersion = newFirmwareVersion;
            flash.NVS_WriteString(&DeviceInfo, "old_firmware", String(oldFirmwareVersion));
        }

        if (millis() - lastStatusTime > statusInterval)
        {
            publishMessage(client, (String(mqttConfig.willTopic) + deviceId).c_str(), offLineMsg(false).c_str());
            lastStatusTime = millis();
        }
    }
}

void reconnect(PubSubClient &client)
{
    if (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(deviceId.c_str(), mqttUserName, mqttPassword, (String(mqttConfig.willTopic) + deviceId).c_str(), mqttConfig.willQos, mqttConfig.willRetain, offLineMsg(true).c_str(), mqttConfig.clearSession))
        {
            Serial.println(F("connected"));
            connectedToNetwork = true;
            client.subscribe((String(mqttConfig.wallet) + deviceId).c_str(), 0);
            client.subscribe((String(mqttConfig.control) + deviceId).c_str(), 0);
            client.subscribe((String(mqttConfig.config) + deviceId).c_str(), 0);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(F(" try again in 5 seconds"));
            connectedToNetwork = false;
            vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
    }
}

bool publishMessage(PubSubClient &client, const char *topic, const char *payload)
{
    if (client.publish(topic, payload))
    {
        // Serial.println("Message published [" + String(topic) + "]: " + payload);
        return true;
    }
    else
    {
        Serial.println(F("error in sending message"));
        connectedToNetwork = false;
        return false;
    }
}

String offLineMsg(bool state)
{
    JsonDocument doc;
    doc["deviceStatus"] = !state ? "online" : "offline";
    doc["id"] = deviceId;
    String output;
    serializeJsonPretty(doc, output);

    Serial.println(output);
    return output;
}

void callback(PubSubClient &client, char *topic, byte *payload, unsigned int length)
{
    String incommingMessage = "";
    for (int i = 0; i < length; i++)
    {
        incommingMessage += (char)payload[i];
    }

    Serial.println(" JSON Message arrived " + incommingMessage);

    if (strcmp(topic, (String(mqttConfig.wallet) + deviceId).c_str()) == 0)
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, incommingMessage);

        if (error)
        {
            Serial.printf("Failed to parse JSON: %s\n", error.c_str());
            return;
        }

        const char *rechargeUnit = doc["unit"];
        const char *id = doc["id"];
        const char *receivedToken = doc["token"];

        if (id == nullptr || rechargeUnit == nullptr || receivedToken == nullptr)
        {
            Serial.println(F("Invalid JSON payload"));
            return;
        }

        if (strcmp(id, deviceId.c_str()) == 0)
        {
            String existingTokens = flash.ReadFile(SPIFFS, "/token.txt");

            if (existingTokens.indexOf(String(receivedToken)) == -1)
            {
                float newRecharge = balUnit + atof(rechargeUnit);
                flash.WriteFile(SPIFFS, "/total_unit.txt", flash.FormatFloatToString(newRecharge));
                vTaskDelay(10);
                flash.WriteFile(SPIFFS, "/storedConsumption.txt", flash.FormatFloatToString(totalUnit));
                vTaskDelay(10);

                readPzem.ResetEnergy();
                vTaskDelay(100);
                flash.AppendFile(SPIFFS, "/token.txt", (String(receivedToken) + "\n").c_str());
                vTaskDelay(100);

                Serial.println("Message arrived [" + String(topic) + "]" + rechargeUnit);
                JsonDocument doc;
                doc["type"] = "wallet recharge";
                doc["msg"] = "successful";
                doc["id"] = deviceId;

                String responseOutput;
                serializeJsonPretty(doc, responseOutput);

                publishMessage(client, (String(mqttConfig.response) + deviceId).c_str(), responseOutput.c_str());
                incommingMessage = "";
                buzzerAlert.PlaySuccess();
                vTaskDelay(100);
            }
            else
            {
                Serial.println(F("Used or invalid token"));
                JsonDocument doc;
                doc["type"] = "wallet recharge";
                doc["msg"] = existingTokens.indexOf(String(receivedToken)) != -1 ? "used token" : "wrong token";
                doc["id"] = deviceId;
                doc["token"] = receivedToken;
                String responseOutput;
                serializeJsonPretty(doc, responseOutput);
                publishMessage(client, (String(mqttConfig.response) + deviceId).c_str(), responseOutput.c_str());
                incommingMessage = "";
                buzzerAlert.PlayWarning();
                vTaskDelay(100);
            }
        }
    }

    if (strcmp(topic, (String(mqttConfig.control) + deviceId).c_str()) == 0)
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, incommingMessage);

        if (error)
        {
            Serial.printf("Failed to parse JSON: %s\n", error.c_str());
            return;
        }

        const char *command = doc["command"];
        const char *id = doc["id"];

        if (id == nullptr || command == nullptr)
        {
            Serial.println(F("Invalid JSON payload"));
            return;
        }

        if (strcmp(id, deviceId.c_str()) == 0)
        {
            handleCommand(client, command);
            incommingMessage = "";
        }
    }

    if (strcmp(topic, (String(mqttConfig.config) + deviceId).c_str()) == 0)
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, incommingMessage);

        if (error)
        {
            Serial.printf("Failed to parse JSON: %s\n", error.c_str());
            return;
        }

        const char *type = doc["type"];
        const char *id = doc["id"];
        const char *command = doc["command"];
        const char *mode = doc["mode"];

        if (id == nullptr || type == nullptr)
        {
            Serial.println(F("Invalid JSON payload"));
            return;
        }

        if (strcmp(id, deviceId.c_str()) == 0)
        {
            if (strcmp(type, "upsMode") == 0 && command != nullptr)
            {
                if (strcmp(command, flash.ReadFile(SPIFFS, "/ups_mode.txt").c_str()) != 0)
                {
                    vTaskDelay(10);
                    flash.WriteFile(SPIFFS, "/ups_mode.txt", command);
                    vTaskDelay(100);
                    sendResponse(client, "upsMode", "successful", deviceId.c_str());
                    incommingMessage = "";
                    buzzerAlert.PlaySuccess();
                    delay(10);
                }
                else
                {
                    sendResponse(client, "upsMode", "duplicate command", deviceId.c_str());
                    incommingMessage = "";
                    buzzerAlert.PlayWarning();
                    delay(10);
                }
            }
            else if (strcmp(type, "deviceMode") == 0 && mode != nullptr)
            {
                if (strcmp(mode, deviceMode) != 0)
                {
                    flash.WriteFile(SPIFFS, "/device_mode.txt", mode);
                    delay(100);

                    sendResponse(client, "deviceMode", "successful", deviceId.c_str());
                    buzzerAlert.PlaySuccess();

                    if (strcmp(mode, "prepaid") == 0)
                    {
                        readPzem.ResetEnergy();
                        delay(10);
                        bool formatted = SPIFFS.format();

                        if (formatted)
                        {
                            Serial.println(F("\n\nSuccess formatting"));
                            ESP.restart();
                        }
                        else
                        {
                            Serial.println(F("\n\nError formatting"));
                        }
                    }
                    else if (strcmp(mode, "check") == 0)
                    {
                        buzzerAlert.PlaySuccess();
                        delay(10);
                        readPzem.ResetEnergy();
                        delay(10);
                    }
                }
                else
                {
                    sendResponse(client, "deviceMode", "duplicate command", deviceId.c_str());
                    buzzerAlert.PlayWarning();
                    delay(10);
                }

                incommingMessage = "";
            }
            else
            {
                Serial.println("Error command. Expected ID: " + String(deviceId) + ", Received: " + String(id));
                sendResponse(client, type, "error command", deviceId.c_str());
                incommingMessage = "";
                buzzerAlert.PlayWarning();
            }
        }
    }
}

void sendResponse(PubSubClient &client, const char *type, const char *msg, const char *id)
{
    JsonDocument doc;
    doc["type"] = type;
    doc["msg"] = msg;
    doc["id"] = deviceId;
    String responseOutput;
    serializeJsonPretty(doc, responseOutput);

    publishMessage(client, (String(mqttConfig.response) + deviceId).c_str(), responseOutput.c_str());
    vTaskDelay(100);
}

void handleCommand(PubSubClient &client, const char *command)
{
    if ((strcmp(command, "lock") == 0 || strcmp(command, "unlock") == 0) && strcmp(command, deviceLock) != 0)
    {
        vTaskDelay(10);
        flash.WriteFile(SPIFFS, "/mLock.txt", command);
        vTaskDelay(10);
        buzzerAlert.PlaySuccess();
        sendResponse(client, (String("device ") + String(command)).c_str(), "successful", deviceId.c_str());
        vTaskDelay(10);
    }
    else if ((strcmp(command, "lock") == 0 || strcmp(command, "unlock") == 0) && strcmp(command, deviceLock) == 0)
    {
        vTaskDelay(10);
        buzzerAlert.PlayWarning();
        sendResponse(client, (String("device ") + String(command)).c_str(), "duplicate command", deviceId.c_str());
        vTaskDelay(10);
    }

    if (strcmp(deviceLock, "lock") == 0)
    {
        if ((strcmp(command, "on") == 0 || strcmp(command, "off") == 0))
        {
            vTaskDelay(10);
            buzzerAlert.PlayWarning();
            sendResponse(client, (String("device ") + String(command)).c_str(), "not successful Contact Admin", deviceId.c_str());
            vTaskDelay(10);
        }
    }

    else if (strcmp(deviceLock, "lock") != 0)
    {
        if ((strcmp(command, "on") == 0 || strcmp(command, "off") == 0) && strcmp(command, String(pwrBState == "on" ? "on" : "off").c_str()) != 0)
        {
            if (strcmp(command, "on") == 0)
            {
                Serial.println(" command received on");
                deviceControl = "on";
                buzzerAlert.PlaySuccess();
                sendResponse(client, (String("device ") + String(command)).c_str(), "successful", deviceId.c_str());
                vTaskDelay(10);
            }
            else if (strcmp(command, "off") == 0)
            {
                Serial.println(" command received off");
                deviceControl = "off";
                buzzerAlert.PlaySuccess();
                sendResponse(client, (String("device ") + String(command)).c_str(), "successful", deviceId.c_str());
                vTaskDelay(10);
            }
        }
        else if ((strcmp(command, "on") == 0 || strcmp(command, "off") == 0) && strcmp(command, String(pwrBState == "on" ? "on" : "off").c_str()) == 0)
        {
            vTaskDelay(10);
            buzzerAlert.PlayWarning();
            sendResponse(client, (String("device ") + String(command)).c_str(), "duplicate command", deviceId.c_str());
            vTaskDelay(10);
        }
        // else
        // {
        //     buzzerAlert.PlayWarning();
        //     sendResponse(client, (String("device ") + String(command)).c_str(), "not successful", deviceId.c_str());
        //     vTaskDelay(10);
        // }
    }

    if (strcmp(command, "reset") == 0)
    {
        sendResponse(client, "device Reset", "successful", deviceId.c_str());
        readPzem.ResetEnergy();
        vTaskDelay(10);
        bool formatted = SPIFFS.format();

        if (formatted)
        {
            Serial.println(F("\n\nSuccess formatting"));
            ESP.restart();
        }
        else
        {
            Serial.println(F("\n\nError formatting"));
        }
    }
}
