#include "led_bulb.h"

LedBulb::LedBulb(int pin)
{
    this->pin = pin;
    this->current_state = LOW;
    pinMode(pin, OUTPUT);
}

uint8_t LedBulb::getState()
{
    return this->current_state;
}

void LedBulb::setState(uint8_t state)
{
    this->current_state = state;
    digitalWrite(this->pin, this->current_state);
}

void LedBulb::toggle()
{
    if (this->getState() == LOW)
    {
        this->setState(HIGH);
    }
    else
    {
        this->setState(LOW);
    }
}
