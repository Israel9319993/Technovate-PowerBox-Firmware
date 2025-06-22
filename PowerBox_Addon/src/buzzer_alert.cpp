#include "buzzer_alert.h"

Buzzer::Buzzer() {}

void Buzzer::PlayIntro()
{
   // Play E5 (659 Hz) three times – each for 125 ms
   tone(_buzzerPin, 659, 125);
   delay(150);
   tone(_buzzerPin, 659, 125);
   delay(150);
   tone(_buzzerPin, 659, 125);
   delay(150);
 
   // Play C5 (523 Hz) once for 125 ms
   tone(_buzzerPin, 523, 125);
   delay(150);
 
   // Play E5 (659 Hz) once for 125 ms
   tone(_buzzerPin, 659, 125);
   delay(150);
 
   // Play G5 (783 Hz) for 250 ms
   tone(_buzzerPin, 783, 250);
   delay(300);
 
   noTone(_buzzerPin);
}

void Buzzer::PlayUpdate()
{
  tone(_buzzerPin, 3135, 250);
  delay(250);
  tone(_buzzerPin, 3135, 250);
  delay(250);
}

void Buzzer::PlayWarning()
{
  for (int i = 0; i < 3; i++)
  {
    tone(_buzzerPin, 440, 300); // A4
    delay(300);
    noTone(_buzzerPin);
    delay(250); // Short pause between beeps
  }
}

void Buzzer::PlaySuccess()
{
  tone(_buzzerPin, 3135, 250);
  delay(250);
  tone(_buzzerPin, 3520, 250);
  delay(150);
  tone(_buzzerPin, 3135, 250);
  delay(250);
  tone(_buzzerPin, 3520, 250);
  delay(250);
}

void Buzzer::PlayConnect()  // BLE Connected
{
    tone(_buzzerPin, 2637, 200); // E6
    delay(200);
    tone(_buzzerPin, 3135, 200); // G6
    delay(200);
    tone(_buzzerPin, 3520, 300); // A6
    delay(300);
    noTone(_buzzerPin);
}

void Buzzer::PlayDisconnect()  // BLE Disconnected
{
    tone(_buzzerPin, 3520, 200); // A6
    delay(200);
    tone(_buzzerPin, 3135, 200); // G6
    delay(200);
    tone(_buzzerPin, 2637, 300); // E6
    delay(300);
    noTone(_buzzerPin);
}
