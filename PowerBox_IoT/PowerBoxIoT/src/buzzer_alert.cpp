#include "buzzer_alert.h"

Buzzer::Buzzer() {}

void Buzzer::PlayIntro()
{
  tone(_buzzerPin, 2093, 300);
  delay(300);
  tone(_buzzerPin, 2637, 300);
  delay(300);
  tone(_buzzerPin, 3135, 300);
  delay(300);
  tone(_buzzerPin, 4186, 300);
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