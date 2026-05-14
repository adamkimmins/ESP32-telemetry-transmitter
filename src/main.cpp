#include <Arduino.h>
#include <heltec_unofficial.h>
#include "../include/SystemController.h"

#define BUTTON_PIN 0

SystemController systemController;
bool lastButtonState = HIGH;

void setup()
{
    heltec_setup(); // unofficial lib setup - kindly handles OLED string vector display/LoRa init
    Serial.begin(115200); // opens the USB serial port at 115200 baud
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    systemController.begin();
}

void loop()
{
    heltec_loop(); // according to docs, must be called every loop as well

    bool currentButtonState = digitalRead(BUTTON_PIN);
    if(currentButtonState == LOW && lastButtonState == HIGH)
    {
        systemController.handleEvent(SystemEvent::BUTTON_PRESS);
        delay(200);
    }
    lastButtonState = currentButtonState;

    systemController.update();
}