#include <Arduino.h>

#define LED_BUILTIN 35
#define BUTTON_PIN 0

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool On = false;
bool lastButtonState = HIGH;

void loop()
{

  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == LOW && lastButtonState == HIGH)
  {
    On = !On;

    // Ending sequence
    if (!On)
    {
      for (int i = 0; i < 3; i++)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);

        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
      }
    }
    delay(200); // Debounce delay
  }

  lastButtonState = currentButtonState;

  // Main Loop
  if (On)
  {

    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);

    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
  else
  {
    digitalRead(BUTTON_PIN) == HIGH 
    ? digitalWrite(LED_BUILTIN, LOW) 
    : digitalWrite(LED_BUILTIN, HIGH);
  }
}