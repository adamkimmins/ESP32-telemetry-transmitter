#pragma once
#include <Arduino.h>

enum class SystemState;

class LEDController
{
private:
    uint8_t ledPin; // 35
    bool isOn;
public:
    LEDController(uint8_t pin);
    void begin();
    void on();
    void off();
    void toggle();
    bool state();
};

// screen, OLED, 128x64, I2C, GPIO 22 (SCL), GPIO 21 (SDA)
class OLEDController
{
public:
    OLEDController();
    void begin();
    void clear();
    void drawConnectionStatus();
    void drawBootScreen();
    void drawSignalStrength(int8_t rssi);
    void drawStatus(SystemState state);
    void drawShutdown();
};