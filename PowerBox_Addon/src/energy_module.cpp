#include "energy_module.h"
#include <HardwareSerial.h> // Include this for UART functions if using Arduino

// Constructor
EnergySensor::EnergySensor(const int rxPin, const int txPin) 
  :  pzem(Serial1, rxPin, txPin),
  rxPin(rxPin), txPin(txPin) {
  
}



float EnergySensor::GetVoltage() {
 return isnan(pzem.voltage())? 0 : pzem.voltage();
}

float EnergySensor::GetCurrent() {
  return isnan(pzem.current())? 0 : pzem.current();
}

float EnergySensor::GetPower() {
    return isnan(pzem.power())? 0 : pzem.power();
}

float EnergySensor::GetFrequency() {
  return isnan(pzem.frequency())? 0 : pzem.frequency();
}


float EnergySensor::GetPowerFactor() {
  return isnan(pzem.pf())? 0 : pzem.pf();
}

float EnergySensor::GetEnergy() {
  return isnan(pzem.energy())? 0 : pzem.energy();
}

void EnergySensor::ResetEnergy() {
pzem.resetEnergy();
}
