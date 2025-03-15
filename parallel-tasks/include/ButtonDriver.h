#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include <Arduino.h>

class ButtonDriver
{
private:
    uint8_t pin;
    bool lastState;
    bool pressedEvent;

public:
    explicit ButtonDriver(uint8_t pinNumber);
    void begin();
    void update();
    bool wasJustPressed();
    bool isHeldDown();
};

#endif
