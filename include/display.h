#include <Arduino.h>

class LEDController
{
private:
    bool isOn = false;
    uint8_t ledPin; //GPIO 35

public:
    LEDController(uint8_t ledPin)
        : ledPin(ledPin), isOn(false) {};

    void *pinMode(uint8_t pin, uint8_t mode);
    void *setup();
};

class OLEDController //uses I2C communication
{
private:
    bool isOn = false;
    uint8_t SCLPin; //GPIO 22
    uint8_t SDAPin; //GPIO 21

public:
    OLEDController(uint8_t SCLPin, uint8_t SDAPin)
        : SCLPin(SCLPin), SDAPin(SDAPin), isOn(false) {};
    void *setup();
    void displayMessage(const char* message);

};