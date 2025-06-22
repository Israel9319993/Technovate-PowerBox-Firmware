#ifndef ENERGY_MODULE_H
#define ENERGY_MODULE_H
#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "global_config.h"

class EnergySensor
{
public:
    EnergySensor(const int rxPin, const int txPin);

    float GetVoltage();                // Read voltage
    float GetCurrent();                // Read current
    float GetPower();                  // Read active power
    float GetFrequency();              // Read frequency
    float GetPowerFactor();            // Read power factor
    float GetEnergy();                 // Read energy
    void ResetEnergy();                // Reset energy counter

private:
   PZEM004Tv30 pzem;
    const int rxPin;
    const int txPin;
   
};

#endif

