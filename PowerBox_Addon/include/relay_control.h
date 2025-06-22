#ifndef RELAY_CONTROL_H
#define RELAY_CONTROL_H
#include "global_config.h"

class Relay
{

public:
    Relay();
    void Begin();
    void MeterOn();
    void MeterOff();
    String GetState();

private:
 bool onFlag = false;
 bool offFlag = false;

};
#endif