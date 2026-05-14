#pragma once
#include <Arduino.h>
#include "Display.h"
#include "Radio.h"
#include "FSM.h"

class SystemController
{
private:
    unsigned long lastUpdateMs;
    SystemState currentState;
    LEDController led;
    OLEDController oled;
    RFController rad;
public:
    SystemController();
    void begin();
    void update();
    void handleEvent(SystemEvent event);
    void changeState(SystemState newState);
    SystemState getState() const { return currentState; }
};