#include "../include/Display.h"
#include "FSM.h"
#include <SSD1306Wire.h>

extern SSD1306Wire display;

//LED
LEDController::LEDController(uint8_t pin)
    : ledPin(pin), isOn(false) {}

void LEDController::begin()
{
    pinMode(ledPin, OUTPUT);
    off();
}
void LEDController::on()  { digitalWrite(ledPin, HIGH); isOn = true; }
void LEDController::off() { digitalWrite(ledPin, LOW);  isOn = false; }
void LEDController::toggle()
{
    isOn = !isOn;
    digitalWrite(ledPin, isOn ? HIGH : LOW);
}
bool LEDController::state() { return isOn; }

// OLED
OLEDController::OLEDController() {}

void OLEDController::begin()
{
    // display.init();
    display.setFont(ArialMT_Plain_10);
    clear();
}

void OLEDController::clear()
{
    display.clear();
    display.display();
}

void OLEDController::drawBootScreen()
{
    display.clear();
    display.drawString(0, 0, "Booting...");
    display.display();
}

void OLEDController::drawSignalStrength(int8_t rssi)
{
    display.clear();
    display.drawString(0, 0, "Status: RUNNING");
    display.drawString(0, 16, "RSSI: " + String(rssi) + " dBm");
    display.display();
}

void OLEDController::drawStatus(SystemState state)
{
    display.clear();
    switch(state)
    {
        case SystemState::OFF:
            display.drawString(0, 0, "Status: OFF"); break;
        case SystemState::BOOTING:
            display.drawString(0, 0, "Status: BOOTING"); break;
        case SystemState::RUNNING:
            display.drawString(0, 0, "Status: RUNNING"); break;
        case SystemState::SHUTDOWN:
            display.drawString(0, 0, "Status: SHUTDOWN"); break;
    }
    display.display();
}

void OLEDController::drawShutdown()
{
    display.clear();
    display.drawString(0, 0, "Shutting down...");
    display.display();
}