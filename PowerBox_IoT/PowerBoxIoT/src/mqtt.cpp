#include "mqtt.h"
#include "flash_mem.h"
#include "ui.h"
#include "notification.h"
#include "task.h"
#include "energy_module.h"

extern EnergySensor readPzem;
extern Flash flash;

unsigned long lastStatusTime = 0;
const unsigned long statusInterval = 30000; // 60 seconds
extern Notification notification;
void setupMQTT(PubSubClient &client)
{
    client.setServer(mqttServer, port);
    client.setCallback([&client](char *topic, byte *payload, unsigned int length)
                       { callback(client, topic, payload, length); });

    client.setBufferSize(6000);
    // espClient.setInsecure();
    // client.setKeepAlive(5);
}

String pushMessage()
{

    JsonDocument doc;

    doc["battVolt"] = battVolt;
    doc["battPercent"] = battPercent;
    doc["cell1"] = cell1;
    doc["cell2"] = cell2;
    doc["cell3"] = cell3;
    doc["cell4"] = cell3;
    doc["balUnit"] = balUnit;
    doc["totalUnit"] = totalUnit;

    doc["battHealth"] = battPercent; // bmsSOH;
    doc["battRCC"] = 100;            // bmsRCC;
    doc["chargeCycles"] = 0;         // chargeCycles;
    doc["battFCC"] = 100;            // bmsFCC;

    doc["solarVoltage"] = solarVoltage;
    doc["solarCurrent"] = solarCurrent;
    doc["acVolt"] = acVolt;
    doc["power"] = pwr;
    doc["usage"] = usage;
    doc["powerFactor"] = powerFactor;
    doc["frequency"] = frequency;
    doc["chargeCurrent"] = chargeCurrent;
    doc["state"] = pwrBState;
    doc["upsFlag"] = upsFlag;
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

    // Check if the client is connected
    if (!client.connected())
    {
        unsigned long now = millis();
        // Try reconnecting every 5 seconds
        if (now - lastReconnectAttempt > 5000)
        {
            lastReconnectAttempt = now;
            reconnect(client); // Attempt to reconnect
        }
    }
    else
    {
        // If connected, process MQTT messages
        client.loop();
        connectedToNetwork = true;
        // Publish messages at defined intervals
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
            flash.NVS_WriteString("old_firmware", String(oldFirmwareVersion));
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
    // Loop until we're reconnected

    if (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        //   if (client.connect(device_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) //Replace with your Thingspeak MQTT Device Credentials
        if (client.connect(deviceId.c_str(), mqttUserName, mqttPassword, (String(mqttConfig.willTopic) + deviceId).c_str(), mqttConfig.willQos, mqttConfig.willRetain, offLineMsg(true).c_str(), mqttConfig.clearSession))
        {
            Serial.println(F("connected"));
            connectedToNetwork = true;
            client.subscribe((String(mqttConfig.wallet) + deviceId).c_str(), 0);  // subscribe the topics here
            client.subscribe((String(mqttConfig.control) + deviceId).c_str(), 0); // subscribe the topics here
            client.subscribe((String(mqttConfig.config) + deviceId).c_str(), 0);  // subscribe the topics here
            // client.subscribe((String(mqttConfig.otaUpdate) + deviceId).c_str(), 0);
            // client.subscribe((String(mqttConfig.otaUpdate) + String("ALL")).c_str(), 0); // subscribe the topics here
            // pushMessage();
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(F(" try again in 5 seconds")); // Wait 5 seconds before retrying
            connectedToNetwork = false;
            vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
    }
}

bool publishMessage(PubSubClient &client, const char *topic, const char *payload)
{
    if (client.publish(topic, payload))
    {
        Serial.println("Message publised [" + String(topic) + "]: " + payload);
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
    // doc["timeStamp"] = !state ? rtc.GetCurrentTime() : "";
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
    // Serial.println(F("first pass"));

    Serial.println(" JSON Message arrived " + incommingMessage);

    if (strcmp(topic, (String(mqttConfig.wallet) + deviceId).c_str()) == 0)
    {
        // Parse the JSON data
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, incommingMessage);

        // Check for JSON parsing errors
        if (error)
        {
            Serial.printf("Failed to parse JSON: %s\n", error.c_str());
            return;
        }

        const char *rechargeUnit = doc["unit"];
        const char *id = doc["id"];
        const char *receivedToken = doc["token"];

        if (strcmp(id, deviceId.c_str()) == 0)
        {
            String existingTokens = flash.ReadFile(SPIFFS, "/token.txt");

            // Check if the token already exists in the file
            if (existingTokens.indexOf(String(receivedToken)) == -1)
            {
                float newRecharge = balUnit + atof(rechargeUnit);
                flash.WriteFile(SPIFFS, "/total_unit.txt", flash.FormatFloatToString(newRecharge));
                vTaskDelay(10);
                flash.WriteFile(SPIFFS, "/storedConsumption.txt", flash.FormatFloatToString(totalUnit));
                vTaskDelay(10);

                // Serial.println("resetAllEnergy");
                readPzem.ResetEnergy();
                vTaskDelay(100);
                notification.DisplayNotification("Wallet Recharge", (String(rechargeUnit) + " Unit Load Successfully").c_str(), "success");
                vTaskDelay(10);
                // _ui_screen_change(&ui_Success_Screen, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_Success_Screen_screen_init);
                // lv_label_set_text(ui_secondSuccessLabel,  (String(rechargeUnit) + " Unit Load Successfully").c_str());
                flash.AppendFile(SPIFFS, "/token.txt", (String(receivedToken) + "\n").c_str()); // Ensure newline for proper formatting
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
                vTaskDelay(100);
            }

            else if (existingTokens.indexOf(String(receivedToken)) != -1)
            {

                Serial.println(F("USed token"));
                notification.DisplayNotification("Unit Recharge Not Successful", "Used Token", "warning");
                vTaskDelay(10);

                Serial.println("Message arrived [" + String(topic) + "]" + rechargeUnit);
                JsonDocument doc;
                doc["type"] = "wallet recharge";
                doc["msg"] = "used token";
                doc["id"] = deviceId;
                doc["token"] = receivedToken;
                String responseOutput;
                serializeJsonPretty(doc, responseOutput);
                publishMessage(client, (String(mqttConfig.response) + deviceId).c_str(), responseOutput.c_str());
                incommingMessage = "";
                vTaskDelay(100);
            }

            else
            {
                Serial.println(F("wrong token"));
                notification.DisplayNotification("Unit Recharge Not Successful", "Wrong Token", "warning");
                vTaskDelay(10);

                Serial.println("Message arrived [" + String(topic) + "]" + rechargeUnit);
                JsonDocument doc;
                doc["type"] = "wallet recharge";
                doc["msg"] = "wrong token";
                doc["id"] = deviceId;
                doc["token"] = receivedToken;
                String responseOutput;
                serializeJsonPretty(doc, responseOutput);
                publishMessage(client, (String(mqttConfig.response) + deviceId).c_str(), responseOutput.c_str());
                incommingMessage = "";
                vTaskDelay(100);
            }
        }
    }
    //     float amount = 0.0f; // Ensure initialization
    //     const char *loadToken = deviceWallet.LoadToken(String(receivedToken), amount);

    //     if (loadToken != nullptr && strcmp(loadToken, "success") == 0)
    //     {
    //                 glcd.Notification((String(amount) + " units Recharged").c_str(), "success");
    //                vTaskDelay(10);

    //                 Serial.println("Message arrived [" + String(topic) + "]" + amount);
    //                 JsonDocument doc;
    //                 doc["type"] = "wallet recharge";
    //                 doc["msg"] = "successful";
    //                 doc["id"] = deviceId;
    //                 doc["token"] = receivedToken;

    //                 String responseOutput;
    //                 serializeJsonPretty(doc, responseOutput);

    //                 publishMessage(client, (String(mqttConfig.response) + deviceId).c_str(), responseOutput.c_str());
    //                 incommingMessage = "";
    //                vTaskDelay(100);
    //                 Serial.println(F("token is successful"));
    //             }

    //             else if (loadToken != nullptr && strcmp(loadToken, "used token") == 0)
    //             {

    //                 Serial.println(F("USed token"));
    //                 glcd.Notification2("Recharge Failed", "Used Token", "warning");
    //                vTaskDelay(10);
    //                 JsonDocument doc;
    //                 doc["type"] = "wallet recharge";
    //                 doc["msg"] = "used token";
    //                 doc["id"] = deviceId;
    //                 doc["token"] = receivedToken;
    //                 String responseOutput;
    //                 serializeJsonPretty(doc, responseOutput);
    //                 publishMessage(client, (String(mqttConfig.response) + deviceId).c_str(), responseOutput.c_str());
    //                 incommingMessage = "";
    //                vTaskDelay(100);
    //             }

    //             else if (loadToken != nullptr && strcmp(loadToken, "invalid token") == 0)
    //             {
    //                 Serial.println(F("USed token"));
    //                 glcd.Notification2("Recharge Failed", "Wrong Token", "warning");
    //                vTaskDelay(10);
    //                 JsonDocument doc;
    //                 doc["type"] = "wallet recharge";
    //                 doc["msg"] = "wrong token";
    //                 doc["id"] = deviceId;
    //                 doc["token"] = receivedToken;
    //                 String responseOutput;
    //                 serializeJsonPretty(doc, responseOutput);
    //                 publishMessage(client, (String(mqttConfig.response) + deviceId).c_str(), responseOutput.c_str());
    //                 incommingMessage = "";
    //                vTaskDelay(100);
    //             }

    //             else
    //             {
    //                 Serial.println(F("Error: Token processing failed"));
    //             }

    if (strcmp(topic, (String(mqttConfig.control) + deviceId).c_str()) == 0)
    {
        // Parse the JSON data

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, incommingMessage);

        // Check for JSON parsing errors
        if (error)
        {
            Serial.printf("Failed to parse JSON: %s\n", error.c_str());
            return;
        }

        const char *command = doc["command"];
        const char *id = doc["id"];

        if (strcmp(id, deviceId.c_str()) == 0)
        {

            handleCommand(client, command);
            incommingMessage = "";
        }
    }

    //     if (strcmp(topic, (String(mqttConfig.otaUpdate) + deviceId).c_str()) == 0 || strcmp(topic, (String(mqttConfig.otaUpdate) + String("ALL")).c_str()) == 0)
    //     {

    //         // Serial.println("I receive update already ");
    //         // Parse the JSON data
    //         JsonDocument doc;
    //         DeserializationError error = deserializeJson(doc, incommingMessage);

    //         // Check for JSON parsing errors
    //         if (error)
    //         {
    //             Serial.printf("Failed to parse JSON: %s\n", error.c_str());
    //             return;
    //         }
    //         Serial.println(" JSON Message arrived " + incommingMessage);
    //         const char *firmwareUrl = doc["firmwareUrl"];
    //         otaAction = doc["action"];
    //         float version = doc["version"];
    //         float currentVersion = flash.NVS_ReadString("new_firmware").toFloat();
    //         firmwareVersion = version;

    //         if (strcmp(otaAction, "upgrade") == 0 && (version > currentVersion))
    //         {
    //             Serial.print("Firmware URL received: ");
    //             Serial.println(F(firmwareUrl));
    //             glcd.Notification2("New Firmware UpGrade", "Available", "update");
    //             // Start firmware update
    //             updateFirmware(String(otaBaseUrl) + firmwareUrl);
    //         }

    //         else if (strcmp(otaAction, "downgrade") == 0 && (version <= currentVersion))
    //         {
    //             Serial.print("Firmware URL received: ");
    //             Serial.println(F(firmwareUrl));
    //             glcd.Notification2("New Firmware DownGrade", "Available", "update");
    //             // Start firmware update
    //             updateFirmware(String(otaBaseUrl) + firmwareUrl);
    //         }
    //     }

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
                    notification.DisplayNotification("UPS Mode", "Command Successful", "success");
                    delay(10);
                }
                else
                {
                    sendResponse(client, "upsMode", "duplicate command", deviceId.c_str());
                    incommingMessage = "";
                    notification.DisplayNotification("Duplicate Command", "UPS Mode already set", "warning");
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
                    notification.DisplayNotification("Device Mode", "Command Successful", "success");

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
                        notification.DisplayNotification("Device Mode Changed", "Command Successful", "success");
                        delay(10);
                        readPzem.ResetEnergy();
                        delay(10);
                    }
                }
                else
                {
                    sendResponse(client, "deviceMode", "duplicate command", deviceId.c_str());
                    notification.DisplayNotification("Warning", "Invalid Command", "warning");
                    delay(10);
                }

                incommingMessage = "";
            }
            else
            {
                Serial.println("Error command. Expected ID: " + String(deviceId) + ", Received: " + String(id));
                sendResponse(client, type, "error command", deviceId.c_str());
                incommingMessage = "";
                notification.DisplayNotification("Error Command", "Invalid Command Received", "warning");
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

    if ((strcmp(command, "lock") == 0 || strcmp(command, "unlock") == 0) && strcmp(command, flash.ReadFile(SPIFFS, "/mLock.txt").c_str()) != 0)
    {
        notification.DisplayNotification((String("PowerBox ") + String(command)).c_str(), "Successfully", "success");
        vTaskDelay(10);
        flash.WriteFile(SPIFFS, "/mLock.txt", command);
        vTaskDelay(10);
        sendResponse(client, (String("device ") + String(command)).c_str(), "successful", deviceId.c_str());
        vTaskDelay(10);
    }

    else if ((strcmp(command, "lock") == 0 || strcmp(command, "unlock") == 0) && strcmp(command, flash.ReadFile(SPIFFS, "/mLock.txt").c_str()) == 0)
    {
        notification.DisplayNotification((String("PowerBox is Already ") + String(command)).c_str(), "Duplicate Command", "warning");
        vTaskDelay(10);
        sendResponse(client, (String("device ") + String(command)).c_str(), "duplicate command", deviceId.c_str());
        vTaskDelay(10);
    }

    if (strcmp("lock", flash.ReadFile(SPIFFS, "/mLock.txt").c_str()) == 0)
    {
        if ((strcmp(command, "on") == 0 || strcmp(command, "off") == 0))
        {

            notification.DisplayNotification("PowerBox is Lock", "Contact Admin", "warning");
            vTaskDelay(10);
            sendResponse(client, (String("device ") + String(command)).c_str(), "not successful Contact Admin", deviceId.c_str());
            vTaskDelay(10);
        }
    }

    else if (strcmp("lock", flash.ReadFile(SPIFFS, "/mLock.txt").c_str()) != 0)
    {
        if ((strcmp(command, "on") == 0 || strcmp(command, "off") == 0) && strcmp(command, (state == 1 ? "on" : "off")) != 0)
        {

            if (strcmp(command, "on") == 0)
            {

                // notification.DisplayNotification((String("PowerBox Turned ") + String(command)).c_str(), "Successfully", "success");
                // vTaskDelay(10);
                Serial.println(" command recieved on");
                deviceControl = "on";
                sendResponse(client, (String("device ") + String(command)).c_str(), "successful", deviceId.c_str());
                vTaskDelay(10);
            }
            else if (strcmp(command, "off") == 0)
            {
                // notification.DisplayNotification((String("PowerBox Turned ") + String(command)).c_str(), "Successfully", "success");
                // vTaskDelay(10);
                Serial.println(" command recieved off");
                deviceControl = "off";
                sendResponse(client, (String("device ") + String(command)).c_str(), "successful", deviceId.c_str());
                vTaskDelay(10);
            }
        }
        else if ((strcmp(command, "on") == 0 || strcmp(command, "off") == 0) && strcmp(command, String(state == 1 ? "on" : "off").c_str()) == 0)
        {

            notification.DisplayNotification(("PowerBox is Already " + String(command)).c_str(), "Duplicate Command", "warning");
            vTaskDelay(10);
            sendResponse(client, (String("device ") + String(command)).c_str(), "duplicate command", deviceId.c_str());
            vTaskDelay(10);
        }

        else
        {
            sendResponse(client, (String("device ") + String(command)).c_str(), "not successful", deviceId.c_str());
            vTaskDelay(10);
        }
    }

    if (strcmp(command, "reset") == 0)
    {
        notification.DisplayNotification("PowerBox Reset", "In Progress", "success");
        delay(2000);
        sendResponse(client, "device Reset", "successful", deviceId.c_str());
     digitalWrite(BCKL, LOW);
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