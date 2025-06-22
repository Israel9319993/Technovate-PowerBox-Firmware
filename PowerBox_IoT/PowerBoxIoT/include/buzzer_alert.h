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

    private:
   const int _buzzerPin = buzzer;
};

#endif