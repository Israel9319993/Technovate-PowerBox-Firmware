#include "relay_control.h"

Relay::Relay() {}
void Relay::Begin()
{
    pinMode(relayPin, OUTPUT);
    // pinMode(relayPin2, OUTPUT);
}

void Relay::MeterOn()
{

    digitalWrite(relayPin, HIGH);
}

void Relay::MeterOff()
{  
    digitalWrite(relayPin, LOW);

}

String Relay:: GetState(){
return digitalRead(relayPin) == HIGH ? "on" : "off";
}

