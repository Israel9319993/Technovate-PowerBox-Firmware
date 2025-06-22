#ifndef INVERTER_READ_H
#define INVERTER_READ_H

#include <Arduino.h>
#include <HardwareSerial.h>

// CRC calculation function
uint16_t calculateCRC(const char* data, int length);

// Structure to hold device rating information
struct DeviceRatingInfo {
  float gridRatingVoltage;
  float gridRatingCurrent;
  float acOutputRatingVoltage;
  float acOutputRatingFrequency;
  float acOutputRatingCurrent;
  int acOutputRatingApparentPower;
  int acOutputRatingActivePower;
  float batteryRatingVoltage;
  float batteryRechargeVoltage;
  float batteryUnderVoltage;
  float batteryBulkVoltage;
  float batteryFloatVoltage;
  int batteryType;
  int maxChargingCurrent;
  int currentMaxChargingCurrent;
  int inputVoltageRange;
  int outputSourcePriority;
  int chargerSourcePriority;
  int parallelMaxNum;
  int machineType;
  int topology;
  int outputMode;
  float batteryReDischargeVoltage;
  int pvOkCondition;
  int pvPowerBalance;
};

// Structure to hold general status parameters
struct GeneralStatusInfo {
  float gridVoltage;
  float gridFrequency;
  float acOutputVoltage;
  float acOutputFrequency;
  int acOutputApparentPower;
  int acOutputActivePower;
  int outputLoadPercent;
  int busVoltage;
  float batteryVoltage;
  int batteryChargingCurrent;
  int batteryCapacity;
  int inverterHeatSinkTemp;
  int pvInputCurrent;
  float pvInputVoltage;
  float batteryVoltageFromSCC;
  int batteryDischargeCurrent;
  uint8_t deviceStatus;
  int batteryVoltageOffset;
  int eepromVersion;
  int pvChargingPower;
  uint8_t deviceStatus2;
};

struct ErrorInfo {
  String name;
  String type;      // "Fault" or "Warning"
  String description;
};

// Error lookup table based on bit positions
const ErrorInfo errorTable[32] = {
  {"Reserved", "", ""},                                    // bit 0
  {"Inverter fault", "Fault", ""},                        // bit 1
  {"Bus Over", "Fault", ""},                              // bit 2
  {"Bus Under", "Fault", ""},                             // bit 3
  {"Bus Soft Fail", "Fault", ""},                         // bit 4
  {"LINE_FAIL", "Warning", ""},                           // bit 5
  {"OPVShort", "Warning", ""},                            // bit 6
  {"Inverter voltage too low", "Fault", ""},              // bit 7
  {"Inverter voltage too high", "Fault", ""},             // bit 8
  {"Over temperature", "Warning", "Compile with a1, if a1=1 fault, otherwise warning"},     // bit 9
  {"Fan locked", "Warning", "Compile with a1, if a1=1 fault, otherwise warning"},          // bit 10
  {"Battery voltage high", "Warning", "Compile with a1, if a1=1 fault, otherwise warning"}, // bit 11
  {"Battery low alarm", "Warning", ""},                   // bit 12
  {"Reserved", "", ""},                                   // bit 13
  {"Battery under shutdown", "Warning", ""},              // bit 14
  {"Reserved", "Warning", ""},                            // bit 15
  {"Over load", "Warning", "Compile with a1, if a1=1 fault, otherwise warning"},           // bit 16
  {"Eeprom fault", "Warning", ""},                        // bit 17
  {"Inverter Over Current", "Fault", ""},                 // bit 18
  {"Inverter Soft Fail", "Fault", ""},                    // bit 19
  {"Self Test Fail", "Fault", ""},                        // bit 20
  {"OP DC Voltage Over", "Fault", ""},                    // bit 21
  {"Bat Open", "Fault", ""},                              // bit 22
  {"Current Sensor Fail", "Fault", ""},                   // bit 23
  {"Battery Short", "Fault", ""},                         // bit 24
  {"Power limit", "Warning", ""},                         // bit 25
  {"PV voltage high", "Warning", ""},                     // bit 26
  {"MPPT overload fault", "Warning", ""},                 // bit 27
  {"MPPT overload warning", "Warning", ""},               // bit 28
  {"Battery too low to charge", "Warning", ""},           // bit 29
  {"Reserved", "", ""},                                   // bit 30
  {"Reserved", "", ""}                                    // bit 31
};











class InverterComm {
private:
  HardwareSerial* serial;
  int rxPin, txPin;
  String response;
  
public:
  // Constructor
  InverterComm(HardwareSerial* ser, int rx, int tx);
  
  // Initialize communication
  void begin(long baud);
  
  // Core communication methods
  bool sendCommand(const char* cmd);
  bool waitForResponse(int timeout = 5000);
  
  // Device information commands
  String getProtocolID();
  String getSerialNumber();
  String getFirmwareVersion();
  String getDeviceMode();
  
  // Status and rating information
  bool getDeviceRatingInfo(DeviceRatingInfo& info);
  bool getGeneralStatus(GeneralStatusInfo& info);
  String getWarningStatus();
  String decodeErrors(String binaryString);
  String* getActiveErrorNames(String binaryString, int& count);
  
  // Setting commands
  bool setOutputSourcePriority(int priority);
  bool setChargerPriority(int priority);
  bool setMaxChargingCurrent(int current);
  bool setMaxUtilityChargingCurrent(int current);
  bool setBatteryType(int type);
  bool setOutputFrequency(int freq);
  bool resetToDefault();
  
  // Enable/Disable functions
  bool enableBuzzer(bool enable);
  bool enablePowerSaving(bool enable);
  bool enableLCDBacklight(bool enable);
  
  // Utility methods
  String getLastResponse();
  void printDeviceStatus(const GeneralStatusInfo& info);
  void printRatingInfo(const DeviceRatingInfo& info);
};

#endif // INVERTER_READ_H