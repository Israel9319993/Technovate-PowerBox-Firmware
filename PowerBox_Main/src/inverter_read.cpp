#include "inverter_read.h"
#include "flash_memory.h"
#include "global_config.h"


float totalRunTimeHours = 0.0;

extern Flash flash;
// CRC calculation function
uint16_t calculateCRC(const char *data, int length)
{
    uint16_t crc = 0;
    for (int i = 0; i < length; i++)
    {
        crc = crc ^ ((uint16_t)data[i] << 8);
        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x8000)
            {
                crc = (crc << 1) ^ 0x1021;
            }
            else
            {
                crc = crc << 1;
            }
        }
    }
    return crc;
}

// Constructor
InverterComm::InverterComm(HardwareSerial *ser, int rx, int tx)
{
    serial = ser;
    rxPin = rx;
    txPin = tx;
}

// Initialize communication
void InverterComm::begin(long baud)
{
    serial->begin(baud, SERIAL_8N1, rxPin, txPin);
}

// Send command with CRC
bool InverterComm::sendCommand(const char *cmd)
{
    String command = String(cmd);
    uint16_t crc = calculateCRC(command.c_str(), command.length());

    // Format CRC as 2 bytes
    char crcBytes[3];
    crcBytes[0] = (crc >> 8) & 0xFF;
    crcBytes[1] = crc & 0xFF;
    crcBytes[2] = '\0';

    // Send command + CRC + CR
    serial->print(command);
    serial->write(crcBytes, 2);
    serial->print('\r');

    return waitForResponse();
}

// Wait for response from device
bool InverterComm::waitForResponse(int timeout)
{
    response = "";
    unsigned long startTime = millis();

    while (millis() - startTime < timeout)
    {
        if (serial->available())
        {
            char c = serial->read();
            if (c == '\r')
            {
                return true;
            }
            response += c;
        }
        delay(10);
    }
    return false;
}

// Get protocol ID
String InverterComm::getProtocolID()
{
    if (sendCommand("QPI"))
    {
        if (response.startsWith("(PI"))
        {
            return response.substring(3, response.length() - 2); // Remove (PI and CRC
        }
    }
    return "";
}

// Get device serial number
String InverterComm::getSerialNumber()
{
    if (sendCommand("QID"))
    {
        if (response.startsWith("("))
        {
            return response.substring(1, response.length() - 2); // Remove ( and CRC
        }
    }
    return "";
}

// Get firmware version
String InverterComm::getFirmwareVersion()
{
    if (sendCommand("QVFW"))
    {
        if (response.startsWith("(VERFW:"))
        {
            return response.substring(7, response.length() - 2); // Remove (VERFW: and CRC
        }
    }
    return "";
}

// Get device mode
String InverterComm::getDeviceMode()
{
    if (sendCommand("QMOD"))
    {
        if (response.startsWith("("))
        {
            char mode = response.charAt(1);
            switch (mode)
            {
            case 'P':
                return "Power On Mode";
            case 'S':
                return "Standby Mode";
            case 'L':
                return "Line Mode";
            case 'B':
                return "Battery Mode";
            case 'F':
                return "Fault Mode";
            case 'H':
                return "Power Saving Mode";
            default:
                return "Unknown Mode";
            }
        }
    }
    return "";
}

// Parse device rating information
bool InverterComm::getDeviceRatingInfo(DeviceRatingInfo &info)
{
    if (sendCommand("QPIRI"))
    {
        if (response.startsWith("("))
        {
            String data = response.substring(1, response.length() - 2); // Remove ( and CRC

            // Parse space-separated values
            int index = 0;
            String values[30];
            int valueCount = 0;

            for (int i = 0; i < data.length(); i++)
            {
                if (data.charAt(i) == ' ')
                {
                    valueCount++;
                    index = 0;
                }
                else
                {
                    if (valueCount < 30)
                    {
                        values[valueCount] += data.charAt(i);
                    }
                }
            }
            valueCount++; // Include last value

            if (valueCount >= 21)
            {
                info.gridRatingVoltage = values[0].toFloat();
                info.gridRatingCurrent = values[1].toFloat();
                info.acOutputRatingVoltage = values[2].toFloat();
                info.acOutputRatingFrequency = values[3].toFloat();
                info.acOutputRatingCurrent = values[4].toFloat();
                info.acOutputRatingApparentPower = values[5].toInt();
                info.acOutputRatingActivePower = values[6].toInt();
                info.batteryRatingVoltage = values[7].toFloat();
                info.batteryRechargeVoltage = values[8].toFloat();
                info.batteryUnderVoltage = values[9].toFloat();
                info.batteryBulkVoltage = values[10].toFloat();
                info.batteryFloatVoltage = values[11].toFloat();
                info.batteryType = values[12].toInt();
                info.maxChargingCurrent = values[13].toInt();
                info.currentMaxChargingCurrent = values[14].toInt();
                info.inputVoltageRange = values[15].toInt();
                info.outputSourcePriority = values[16].toInt();
                info.chargerSourcePriority = values[17].toInt();
                info.parallelMaxNum = values[18].toInt();
                info.machineType = values[19].toInt();
                info.topology = values[20].toInt();

                if (valueCount >= 24)
                {
                    info.outputMode = values[21].toInt();
                    info.batteryReDischargeVoltage = values[22].toFloat();
                    info.pvOkCondition = values[23].toInt();
                    if (valueCount >= 25)
                    {
                        info.pvPowerBalance = values[24].toInt();
                    }
                }
                return true;
            }
        }
    }
    return false;
}

// Parse general status parameters
bool InverterComm::getGeneralStatus(GeneralStatusInfo &info)
{
    if (sendCommand("QPIGS"))
    {
        if (response.startsWith("("))
        {
            String data = response.substring(1, response.length() - 2); // Remove ( and CRC

            // Parse space-separated values
            String values[30];
            int valueCount = 0;
            int startIdx = 0;

            for (int i = 0; i <= data.length(); i++)
            {
                if (i == data.length() || data.charAt(i) == ' ')
                {
                    if (i > startIdx && valueCount < 30)
                    {
                        values[valueCount] = data.substring(startIdx, i);
                        valueCount++;
                    }
                    startIdx = i + 1;
                }
            }

            if (valueCount >= 21)
            {
                info.gridVoltage = values[0].toFloat();
                info.gridFrequency = values[1].toFloat();
                info.acOutputVoltage = values[2].toFloat();
                info.acOutputFrequency = values[3].toFloat();
                info.acOutputApparentPower = values[4].toInt();
                info.acOutputActivePower = values[5].toInt();
                info.outputLoadPercent = values[6].toInt();
                info.busVoltage = values[7].toInt();
                info.batteryVoltage = values[8].toFloat();
                info.batteryChargingCurrent = values[9].toInt();
                info.batteryCapacity = values[10].toInt();
                info.inverterHeatSinkTemp = values[11].toInt();
                info.pvInputCurrent = values[12].toInt();
                info.pvInputVoltage = values[13].toFloat();
                info.batteryVoltageFromSCC = values[14].toFloat();
                info.batteryDischargeCurrent = values[15].toInt();






                // Parse device status bits
                if (valueCount >= 17)
                {
                    String statusStr = values[16];
                    info.deviceStatus = 0;
                    for (int i = 0; i < statusStr.length() && i < 8; i++)
                    {
                        if (statusStr.charAt(i) == '1')
                        {
                            info.deviceStatus |= (1 << (7 - i));
                        }
                    }
                }

                if (valueCount >= 21)
                {
                    info.batteryVoltageOffset = values[17].toInt();
                    info.eepromVersion = values[18].toInt();
                    info.pvChargingPower = values[19].toInt();

                    // Parse second device status
                    if (valueCount >= 21)
                    {
                        String status2Str = values[20];
                        info.deviceStatus2 = 0;
                        for (int i = 0; i < status2Str.length() && i < 8; i++)
                        {
                            if (status2Str.charAt(i) == '1')
                            {
                                info.deviceStatus2 |= (1 << (7 - i));
                            }
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}

// Get warning status
String InverterComm::getWarningStatus()
{
    if (sendCommand("QPIWS"))
    {
        if (response.startsWith("("))
        {
            return response.substring(1, response.length() - 2); // Remove ( and CRC
        }
    }
    return "";
}

String InverterComm::decodeErrors(String binaryString) {
 String activeErrors = "";
  int errorCount = 0;
  
  // Check each bit position (excluding bit 0)
  // String index 0 = bit 31 (leftmost), String index 30 = bit 1 (rightmost, excluding bit 0)
  for (int bit = 1; bit < 32; bit++) {
    int stringIndex = bit; // Convert bit position to string index
    
    if (binaryString.charAt(stringIndex) == '1') {
      // Bit is set, add error to string
      if (errorCount > 0) {
        activeErrors += " | ";
      }
      
      if (errorTable[bit].name != "Reserved" && errorTable[bit].name != "") {
        activeErrors += "b" + String(bit) + ": " + errorTable[bit].name;
        if (errorTable[bit].type != "") {
          activeErrors += " (" + errorTable[bit].type + ")";
        }
      } else {
        activeErrors += "b" + String(bit) + ": Reserved";
      }
      errorCount++;
    }
  }
  
  if (errorCount == 0) {
    return "No errors detected";
  }
  
  return activeErrors;

}

String* InverterComm::getActiveErrorNames(String binaryString, int& count) {
  static String errors[32]; // Static array to return
  count = 0;
  
  for (int bit = 1; bit < 32; bit++) { // Exclude bit 0
    int stringIndex = bit;
    
    if (binaryString.charAt(stringIndex) == '1') {
      if (errorTable[bit].name != "Reserved" && errorTable[bit].name != "" && errorTable[bit].name != "LINE_FAIL") {
        errors[count] = errorTable[bit].name;
        count++;
      }
    }
  }
  
  return errors;
}









// Setting commands
bool InverterComm::setOutputSourcePriority(int priority)
{
    char cmd[10];
    sprintf(cmd, "POP%02d", priority);
    return sendCommand(cmd) && response.startsWith("(ACK");
}

bool InverterComm::setChargerPriority(int priority)
{
    char cmd[10];
    sprintf(cmd, "PCP%02d", priority);
    return sendCommand(cmd) && response.startsWith("(ACK");
}

bool InverterComm::setMaxChargingCurrent(int current)
{
    char cmd[15];
    sprintf(cmd, "MCHGC%03d", current);
    return sendCommand(cmd) && response.startsWith("(ACK");
}

bool InverterComm::setMaxUtilityChargingCurrent(int current)
{
    char cmd[15];
    sprintf(cmd, "MUCHGC%03d", current);
    return sendCommand(cmd) && response.startsWith("(ACK");
}


bool InverterComm::setBatteryType(int type)
{
    char cmd[10];
    sprintf(cmd, "PBT%02d", type);
    return sendCommand(cmd) && response.startsWith("(ACK");
}

bool InverterComm::setOutputFrequency(int freq)
{
    char cmd[10];
    sprintf(cmd, "F%02d", freq);
    return sendCommand(cmd) && response.startsWith("(ACK");
}

// Reset to default settings
bool InverterComm::resetToDefault()
{
    return sendCommand("PF") && response.startsWith("(ACK");
}

// Enable/Disable functions
bool InverterComm::enableBuzzer(bool enable)
{
    return sendCommand(enable ? "PEA" : "PDA") && response.startsWith("(ACK");
}

bool InverterComm::enablePowerSaving(bool enable)
{
    return sendCommand(enable == true ? "PEJ" : "PDJ") && response.startsWith("(ACK");
}

bool InverterComm::enableLCDBacklight(bool enable)
{
    return sendCommand(enable ? "PEX" : "PDX") && response.startsWith("(ACK");
}

// Get last response for debugging
String InverterComm::getLastResponse()
{
    return response;
}

// Print device status in human readable format
void InverterComm::printDeviceStatus(const GeneralStatusInfo &info)
{
    Serial.println("=== Device Status ===");
    Serial.printf("Grid Voltage: %.1f V\n", info.gridVoltage);
    Serial.printf("Grid Frequency: %.1f Hz\n", info.gridFrequency);
    Serial.printf("AC Output Voltage: %.1f V\n", info.acOutputVoltage);
    Serial.printf("AC Output Frequency: %.1f Hz\n", info.acOutputFrequency);
    Serial.printf("AC Output Power: %d VA / %d W\n", info.acOutputApparentPower, info.acOutputActivePower);
    Serial.printf("powerFactor: %.2f\n", (float)info.acOutputActivePower / info.acOutputApparentPower);
    Serial.printf("Load: %d%%\n", info.outputLoadPercent);
    Serial.printf("Bus Voltage: %.2f V\n", info.busVoltage);
    Serial.printf("Battery Voltage: %.2f V\n", info.batteryVoltage);
    Serial.printf("Battery Capacity: %d%%\n", info.batteryCapacity);
      Serial.printf("Battery Voltage from SCC: %d%%\n", info.batteryVoltageFromSCC);
    Serial.printf("Battery Discharge Current: %d A\n", info.batteryDischargeCurrent);
    Serial.printf("Battery Charging Current: %d A\n", info.batteryChargingCurrent);
    Serial.printf("PV Input Voltage: %.1f V\n", info.pvInputVoltage);
    Serial.printf("PV Input Current: %d A\n", info.pvInputCurrent);
    Serial.printf("PV Charging Power: %d W\n", info.pvChargingPower);
    Serial.printf("Temperature: %d°C\n", info.inverterHeatSinkTemp);

 int64_t currentTime = esp_timer_get_time();
  float timeDiffSec = (currentTime) / 1e6;
float powerWatts = info.acOutputActivePower;
totalRunTimeHours = timeDiffSec / 3600.0; // Convert seconds to hours

int deltaSeconds = (int)(timeDiffSec);
// Update last time

lastTime = currentTime;
// Calculate energy usage
usage = (powerWatts/1000.0) * totalRunTimeHours; // Convert to kWh

// Save to NVS if usage changed significantly (using fabs for float)
// if (fabs(previousUsage - usage) >= 0.0001) {
//   previousUsage = usage;
//   // flash.NVS_WriteString(&EnergyInfo, "usage", String(usage, 6));
// }

Serial.printf("Power: %.2fW | Total Usage: %.6f kWh | Runtime: %.2f hours | Seconds: %d\n", 
              powerWatts, usage, totalRunTimeHours, deltaSeconds);
 // 1 second delay between readings
// Convert to kW for usage

    // Decode status bits
    Serial.println("Status Flags:");
    if (info.deviceStatus & 0x01)
        Serial.println("  - AC Charging");
    if (info.deviceStatus & 0x02)
        Serial.println("  - SCC Charging");
    if (info.deviceStatus & 0x04)
        Serial.println("  - Charging On");
    if (info.deviceStatus & 0x10)
        Serial.println("  - Load On");
    if (info.deviceStatus & 0x40)
        Serial.println("  - Configuration Changed");
    if (info.deviceStatus & 0x80)
        Serial.println("  - SBU Priority Version");
}

void InverterComm::printRatingInfo(const DeviceRatingInfo &info)
{
    Serial.println("=== Device Rating Information ===");
    Serial.printf("Grid Rating: %.1f V, %.1f A\n", info.gridRatingVoltage, info.gridRatingCurrent);
    Serial.printf("AC Output Rating: %.1f V, %.1f Hz, %.1f A\n",
                  info.acOutputRatingVoltage, info.acOutputRatingFrequency, info.acOutputRatingCurrent);
    Serial.printf("Power Rating: %d VA / %d W\n", info.acOutputRatingApparentPower, info.acOutputRatingActivePower);
    Serial.printf("Battery Rating: %.1f V\n", info.batteryRatingVoltage);
    Serial.printf("Battery Voltages - Recharge: %.1f V, Under: %.1f V, Bulk: %.1f V, Float: %.1f V\n",
                  info.batteryRechargeVoltage, info.batteryUnderVoltage, info.batteryBulkVoltage, info.batteryFloatVoltage);
    Serial.printf("Max Charging Current: %d A\n", info.maxChargingCurrent);
    Serial.printf("Battery Type: %s\n", info.batteryType == 0 ? "AGM" : info.batteryType == 1 ? "Flooded"
                                                                                              : "User");
    Serial.printf("Output Source Priority: %s\n",
                  info.outputSourcePriority == 0 ? "Utility First" : info.outputSourcePriority == 1 ? "Solar First"
                                                                                                    : "SBU First");
    Serial.printf("Machine Type: %s\n",
                  info.machineType == 0 ? "Grid Tie" : info.machineType == 1 ? "Off Grid"
                                                                             : "Hybrid");
}