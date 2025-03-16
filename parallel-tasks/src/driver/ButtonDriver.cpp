#include "ButtonDriver.h"

ButtonDriver::ButtonDriver(uint8_t pinNumber)
    : pin(pinNumber),
      lastState(false),
      pressedEvent(false)
{
}

void ButtonDriver::begin()
{
    pinMode(pin, INPUT_PULLUP);
    lastState = (digitalRead(pin) == LOW);
}

void ButtonDriver::update()
{
    pressedEvent = false;
    bool currentState = (digitalRead(pin) == LOW);

    if (!lastState && currentState)
    {
        pressedEvent = true;
    }

    lastState = currentState;
}

bool ButtonDriver::wasJustPressed()
{
    return pressedEvent;
}

bool ButtonDriver::isHeldDown()
{
    return lastState;
}
