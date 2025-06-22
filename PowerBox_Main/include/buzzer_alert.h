#ifndef BUZZER_ALERT_H
#define BUZZER_ALAERT_H

#include "global_config.h"

class Buzzer
{

public:
    Buzzer();
    void PlayIntro();   // Replaced Intro with buzzerIntro
    void PlayUpdate();  // Replaced Update with buzzerUpdate
    void PlayWarning(); // Replaced Warning with buzzerWarning
    void PlaySuccess(); // Replaced Successful with buzzerSuccess
    void PlayConnect();      // Replaced Connect with buzzerConnect
    void PlayDisconnect();   // Replaced Disconnect with buzzerDisconnect

    private:
   const int _buzzerPin = buzzer;
};

#endif