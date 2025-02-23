#include "led.h"

Led::Led(int pin)
{
    this->pin = pin;
    this->current_state = LOW;
    pinMode(pin, OUTPUT);
}

uint8_t Led::getState()
{
    return this->current_state;
}

void Led::setState(uint8_t state)
{
    this->current_state = state;
    digitalWrite(this->pin, this->current_state);
}

void Led::toggle()
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
