#ifndef BMS_READ_H
#define BMS_READ_H
#include <Arduino.h>
#include "global_config.h"

#include "driver/uart.h"



class ReadBMS
{
public:
    ReadBMS();
    void BMSInit(uint8_t rxPin, uint8_t txPin, uint32_t baudRate);
    void sendModbusRequest();
    void readModbusResponse();


private:
   int maxPositvieValue = 32767; // Maximum positive value for 16-bit signed integer
  
};

#endif