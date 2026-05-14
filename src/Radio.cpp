#include <Arduino.h>
#include "Radio.h"
#include <modules/SX126x/SX1262.h>

extern SX1262 radio;

RFController::RFController(uint8_t cePin, uint8_t csPin)
    : cePin(cePin), csPin(csPin), isConnected(false) {}

void RFController::begin()
{
    pinMode(cePin, OUTPUT);
    pinMode(csPin, OUTPUT);
    disconnect();
}
void RFController::connect()    { digitalWrite(cePin, HIGH); isConnected = true; }
void RFController::disconnect() { digitalWrite(cePin, LOW); isConnected = false; }
bool RFController::connectionStatus() { return isConnected; }

int8_t RFController::getSignalStrength()
{
    return radio.getRSSI();
}
