#include "notification.h"
#define RED_LED_PIN 25  // Change as needed
#define BLUE_LED_PIN 26 // Change as needed

Notification::Notification() {}

void Notification::begin()
{
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    digitalWrite(RED_LED_PIN, LOW);  // Initialize RED LED to OFF
    digitalWrite(BLUE_LED_PIN, LOW); // Initialize BLUE LED to OFF
}

void Notification::notifyWiFiConnected(bool status, bool status2)
{
    if (status && status2)
    {
        blink(BLUE_LED_PIN, 3); // Blink 1 time if not connected
    }
    else if (status && !status2)
    {
        blink(BLUE_LED_PIN, 1); // Blink 1 time if not connected
    }
    else if (!status && status2)
    {
        blink(RED_LED_PIN, 1); // Blink 1 time if not connected
    }

    else
    {
        digitalWrite(BLUE_LED_PIN, LOW); // ON when connected
    }
}

void Notification::notifyBLEConnected(bool status)
{
    if (status)
    {
        blink(RED_LED_PIN, 3); // Blink 2 times if not connected
    }
    else
    {
    digitalWrite(RED_LED_PIN, LOW); // ON when connected
    }
}

// void Notification::notifyMqttConnected(bool status)
// {
//     if (status)
//     {
//         blink(BLUE_LED_PIN, 1); // Blink 3 times if not connected    
//     }
//     else
//     {
//       digitalWrite(BLUE_LED_PIN, LOW); // OFF when not connected

//     }
// }
