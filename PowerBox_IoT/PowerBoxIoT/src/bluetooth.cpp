#include "bluetooth.h"
#include "flash_mem.h"
#include "notification.h"
#include "task.h"
#include "energy_module.h"

NimBLEServer *pServer = nullptr;
NimBLEService *pService = nullptr;
NimBLECharacteristic *pTxCharacteristic = nullptr;
NimBLECharacteristic *pTTxCharacteristic = nullptr;
NimBLECharacteristic *pRxCharacteristic = nullptr;
// Initialize global variables
std::string dataIn;

extern Flash flash;
// extern Buzzer buzzerAlert;
extern EnergySensor readPzem;
extern Notification notification;
// Server callbacks to handle connection events
class ServerCallbacks : public NimBLEServerCallbacks
{
    void onConnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo) override
    {
        Serial.printf("Client connected: %s\n", connInfo.getAddress().toString().c_str());
        bleConnected = true;
        // buzzerAlert.PlayConnect();
        if (bleTaskHandle != NULL)
        {
            vTaskResume(bleTaskHandle);
        }
       
    }

    void onDisconnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo, int reason) override
    {
        Serial.println("Client disconnected");
        bleConnected = false;
        NimBLEDevice::startAdvertising(); // Restart advertising on disconnect
        // buzzerAlert.PlayDisconnect();
        if (bleTaskHandle != NULL)
        {
            vTaskSuspend(bleTaskHandle);
        }
    }
};

// Characteristic callbacks to handle read/write events
class CharacteristicCallbacks : public NimBLECharacteristicCallbacks
{

    void onWrite(NimBLECharacteristic *pCharacteristic, NimBLEConnInfo &connInfo) override
    {
        // Get the incoming data
        dataIn = pCharacteristic->getValue();
        Serial.printf("Data received: %s\n", dataIn.c_str());

        // Parse the JSON data
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, dataIn);

        // Check for JSON parsing errors
        if (error)
        {
            Serial.printf("Failed to parse JSON: %s\n", error.c_str());
            return;
        }

        // Extract fields from JSON
        const char *type = doc["type"];
        const char *id = doc["id"];

        // Validate the ID
        if (strcmp(id, deviceId.c_str()) == 0)
        {
            // Check if the type is "control"
            if (strcmp(type, "control") == 0)
            {
                const char *command = doc["data"]["command"];
                if (command)
                {
                    // Handle the BLE command
                    Ble::HandleBleCommand(command);
                }
                else
                {
                    Serial.println("Command field is missing in JSON data");
                    Ble::SendResponse((String("device ") + String(command)).c_str(), (String("device is already ") + String(command)).c_str(), deviceId.c_str());
                }
            }

            else if (strcmp(type, "wallet") == 0)
            {
                // const char *token = doc["token"];
                // if (token)
                // {
                //     float amount = 0.0f; // Ensure initialization
                //     // const char *loadToken = deviceWallet.LoadToken(String(token), amount);

                //     if (loadToken != nullptr && strcmp(loadToken, "success") == 0)
                //     {
                //         // Notify the user

                //         // glcd.Notification((String(amount) + " units Recharged").c_str(), "success");
                //         // delay(10);
                //         buzzerAlert.PlaySuccess();
                //         // Send a response to the client
                //         Ble::SendResponse((String(amount) + " units Recharged").c_str(), "successful", deviceId.c_str());
                //     }

                //     else if (loadToken != nullptr && strcmp(loadToken, "used token") == 0)
                //     {
                //         Serial.println("Used token");

                //         // delay(10);
                //         buzzerAlert.PlayWarning();
                //         // Send a response to the client
                //         Ble::SendResponse("wallet", "used token", deviceId.c_str());

                //         // glcd.Notification2("Recharge Failed", "Used Token", "warning");
                //         // glcd.Clear();
                //     }

                //     else
                //     {
                //         Serial.println("CRC Mismatch! Token Invalid.");
                //         // glcd.Notification2("Recharge Failed", "Invalid Token", "warning");
                //         // delay(10);
                //         buzzerAlert.PlayWarning();
                //         // Send a response to the client
                //         Ble::SendResponse("wallet", "invalid token", deviceId.c_str());
                //     }

                //     // Load the token and process it
                //     // deviceWallet.LoadToken(token);
                // }
                // else
                // {
                //     Serial.println("Token field is missing in JSON data");
                //     Ble::SendResponse("wallet", "fail", deviceId.c_str());
                // }

                JsonDocument doc;
                DeserializationError error = deserializeJson(doc, dataIn);
        
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
                        notification.DisplayNotification("Wallet Recharge", (String(rechargeUnit) + " Unit Load Successfully").c_str(), "success");
                        // Send a response to the client
                        Ble::SendResponse((String(rechargeUnit) + " units Recharged").c_str(), "successful", deviceId.c_str());
                        vTaskDelay(100);
                    }
                    else if (existingTokens.indexOf(String(receivedToken)) != -1)
                    {
                        Serial.println(F("Used token"));
                        notification.DisplayNotification("Wallet Recharge", "Used Token Detected", "warning");
                        // Send a response to the client
                        Ble::SendResponse("wallet", "used token", deviceId.c_str());
                       dataIn = "";
                        vTaskDelay(100);
                    }
                    else
                    {
                        Serial.println("CRC Mismatch! Token Invalid.");
                        notification.DisplayNotification("Wallet Recharge", "Invalid Token Detected", "warning");
                        // Send a response to the client
                        Ble::SendResponse("wallet", "invalid token", deviceId.c_str());
                        dataIn = "";
                    }
                   
                   
                }
            }

          
            else if (strcmp(type, "wifiConfig") == 0)
            {
                const char *bleSsid = doc["data"]["ssid"];
                const char *blePassword = doc["data"]["password"];

                if (bleSsid && blePassword)
                {
                    flash.WriteFile(SPIFFS, "/ssid.txt", bleSsid);
                    delay(10);
                    flash.WriteFile(SPIFFS, "/password.txt", blePassword);
                    delay(10);
                    // Restart the ESP to apply changes
                    // buzzerAlert.PlaySuccess();
                    notification.DisplayNotification("Wifi Credentials", "Set Successfully", "success");
                    delay(100);
                    Ble::SendResponse("wifiConfig", "successful", deviceId.c_str());
                    delay(100);
                    notification.DisplayNotification("Device Restarting", "Please Wait", "alert");
                    delay(6000);
                    ESP.restart();
                }
                else
                {
                    Serial.println("Command field is missing in JSON data");
                    Ble::SendResponse("wifiConfig", "fail", deviceId.c_str());
                }
            }

           
            else
            {
                Serial.printf("Unknown type: %s\n", type);
            }
        }
        else
        {
            Serial.printf("ID mismatch. Expected: %s, Received: %s\n", deviceId.c_str(), id);
        }

        // Clear the input data
        dataIn = "";
    }

    void onRead(NimBLECharacteristic *pCharacteristic, NimBLEConnInfo &connInfo) override
    {
        Serial.printf("Data read: %s\n", pCharacteristic->getValue().c_str());
    }
};

// Constructor for the Ble class
// Constructor for the Ble class
Ble::Ble() {} // Initialize members if needed

// Method to initialize BLE and start advertising
void Ble::Begin(const char *id)
{
    Serial.println("Starting NimBLE Server");

    // Construct the device name dynamically
    std::string deviceName = "PB_" + std::string(id);

    // Initialize BLE with the dynamic name
    NimBLEDevice::init(deviceName.c_str()); // Set the device name here

    // Create the BLE server and set callbacks
    pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());
      // Create BLE service
      NimBLEService *pService = pServer->createService(SERVICE_UUID);

    // Create the BLE service
    // pService = pServer->createService(SERVICE_UUID);

    // Create the TX characteristic (for notifications)
    pTxCharacteristic = pService->createCharacteristic(
        TX_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ);
        pTxCharacteristic->setValue("Response");


    // Create the RX characteristic (for read/write)
    pTTxCharacteristic = pService->createCharacteristic(
        TTX_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ);
        pTTxCharacteristic->setValue("device Data");

    // Create the RX characteristic (for read/write)
    pRxCharacteristic = pService->createCharacteristic(
        RX_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE);
        pRxCharacteristic->setValue("Receive Data");
    // Set callbacks for the RX characteristic
    pRxCharacteristic->setCallbacks(new CharacteristicCallbacks());

    // Start the BLE service
    pService->start();

    // Configure and start advertising
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID); // Advertise the service UUID

    // Include the name in the advertising packet
    NimBLEAdvertisementData advertisementData;
    advertisementData.setName(deviceName);
    pAdvertising->setAdvertisementData(advertisementData);

    // Optionally, include the name in the scan response as well
    NimBLEAdvertisementData scanResponseData;
    scanResponseData.setName(deviceName);
    pAdvertising->setScanResponseData(scanResponseData);

    pAdvertising->enableScanResponse(true); // Enable scan response
    pAdvertising->start();                  // Start advertising
    Serial.println("BLE Advertising started");

}

void Ble::HandleBleCommand(const char *command)
{

    String lockStatus = flash.ReadFile(SPIFFS, "/mLock.txt");
    // String controlStatus = flash.ReadFile(SPIFFS, "/mControl.txt");
    if (strcmp("lock", lockStatus.c_str()) == 0)
    {
        // buzzerAlert.PlayWarning();
        notification.DisplayNotification("Device Locked", "Contact Admin", "warning");
        SendResponse((String("device ") + String(command)).c_str(), "device is Locked. Contact Admin", deviceId.c_str());
    }
    else
    {
        if ((strcmp(command, "on") == 0 || strcmp(command, "off") == 0) && strcmp(command, String(pwrBState).c_str()) != 0)
        {
            // buzzerAlert.PlaySuccess();
            // glcd.Notification((String("device turned ") + String(command)).c_str(), "success");
            if (strcmp(command, "on") == 0)
            {
                Serial.println(" command received on");
                deviceControl = "on";
                // buzzerAlert.PlaySuccess();
                notification.DisplayNotification("Device Control", (String("Device turned ") + String(command) + " successfully").c_str(), "success");
                SendResponse((String("device ") + String(command)).c_str(), "successful", deviceId.c_str());
                vTaskDelay(10);
            }
            else if (strcmp(command, "off") == 0)
            {
                Serial.println(" command received off");
                deviceControl = "off";
                // buzzerAlert.PlaySuccess();
                notification.DisplayNotification("Device Control", (String("Device turned ") + String(command) + " successfully").c_str(), "success");
                SendResponse((String("device ") + String(command)).c_str(), "successful", deviceId.c_str());
                vTaskDelay(10);
            }
            delay(10);
        
       
        }
        else
        {
            // buzzerAlert.PlayWarning();
            // glcd.Notification((String("device is already ") + String(command)).c_str(), "warning");
            // buzzerAlert.PlayWarning();
            notification.DisplayNotification("Device Control", (String("Device is already ") + String(command)).c_str(), "warning");
            SendResponse((String("device ") + String(command)).c_str(), (String("device is already ") + String(command)).c_str(), deviceId.c_str());
       
        }
    }
}

void Ble::SendResponse(const char *type, const char *msg, const char *deviceId)
{

    JsonDocument doc;
    doc["type"] = type;
    doc["msg"] = msg;
    doc["id"] = deviceId;
    String responseOutput;
    serializeJsonPretty(doc, responseOutput);

    pTxCharacteristic->setValue((uint8_t *)responseOutput.c_str(), responseOutput.length());
    pTxCharacteristic->notify();
    vTaskDelay(100);
}