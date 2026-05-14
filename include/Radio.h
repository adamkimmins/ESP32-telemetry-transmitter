#pragma once
#include <Arduino.h>

class RFController {
private:
    uint8_t cePin; //GPIO 9
    uint8_t csPin; //GPIO 10
    bool isConnected;
public:
    RFController(uint8_t cePin, uint8_t csPin);

    void begin();

    void connect();

    void disconnect();

    int8_t getSignalStrength();

    bool connectionStatus();

};