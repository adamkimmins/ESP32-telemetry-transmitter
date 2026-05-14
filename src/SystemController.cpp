#include "../include/SystemController.h"

extern void heltec_led(int percent);

// SystemController implementation on Heltec V4 ESP32 hardware specifics; 
// Both OLED pins omitted for the heltec_unofficial lib implementation
SystemController::SystemController()
    : lastUpdateMs(0),
    led(35),
      oled(),
      rad(17, 5),
      currentState(SystemState::OFF)
{}

//init, not start
void SystemController::begin()
{
    Serial.println("LED begin...");
    led.begin();
    Serial.println("OLED begin...");
    oled.begin();
    Serial.println("Radio begin...");
    rad.begin();
    Serial.println("BOOTING...");
    changeState(SystemState::BOOTING);
}

// For simplicity, update will handle all state-specific behavior and transitions;
// Then handleEvent will only trigger state changes based on events
void SystemController::update()
{
    switch (currentState)
    {
    case SystemState::OFF:
        break;

    case SystemState::BOOTING:
        oled.drawBootScreen();
        for (int i = 0; i < 6; i++)
        {
            heltec_led(i % 2 == 0 ? 255 : 0); // red LED on/off
            delay(50);
        }
        heltec_led(0);
        led.on();
        changeState(SystemState::RUNNING);
        break;

    case SystemState::RUNNING: {
        unsigned long now = millis();
        if (now - lastUpdateMs >= 1000) // Update every 1 second
        {
            lastUpdateMs = now;
            int8_t rssi = rad.getSignalStrength();
            oled.drawSignalStrength(rssi);
            Serial.println(rssi);
        }
        break;
    }

    case SystemState::SHUTDOWN: 
        led.off();
        oled.drawShutdown();
        delay(1000);
        changeState(SystemState::OFF);
        break;
    }
}

void SystemController::changeState(SystemState newState)
{
    currentState = newState;
}

void SystemController::handleEvent(SystemEvent event)
{
    switch (event)
    {
    case SystemEvent::START:
        if (currentState == SystemState::OFF)
            changeState(SystemState::BOOTING);
        break;
    case SystemEvent::STOP:
        if (currentState == SystemState::RUNNING)
            changeState(SystemState::SHUTDOWN);
        break;
    case SystemEvent::BUTTON_PRESS:
        if (currentState == SystemState::RUNNING)
            changeState(SystemState::SHUTDOWN);
        else if (currentState == SystemState::OFF || currentState == SystemState::SHUTDOWN)
            changeState(SystemState::BOOTING);
        break;
    }
}