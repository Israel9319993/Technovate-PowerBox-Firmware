#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <Arduino.h>
class Notification
{

public:
    Notification();
    void begin();
    void notifyWiFiConnected(bool status, bool status2);
    void notifyBLEConnected(bool status);
    void notifyMqttConnected(bool status);

private:
    void blink(int pin, int times)
    {
        unsigned long previousMillis = 0;
        int state = LOW;
        int count = 0;
        while (count < times)
        {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= 200)
            {
            previousMillis = currentMillis;
            state = !state;
            digitalWrite(pin, state);
            if (state == LOW)
            {
                count++;
            }
            }
        }
    }
};

#endif