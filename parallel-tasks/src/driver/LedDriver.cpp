#include "LedDriver.h"

LedDriver::LedDriver(uint8_t pinNumber)
    : pin(pinNumber),
      state(false)
{
}

void LedDriver::begin()
{
    pinMode(pin, OUTPUT);
    off();
}

void LedDriver::on()
{
    state = true;
    digitalWrite(pin, HIGH);
}

void LedDriver::off()
{
    state = false;
    digitalWrite(pin, LOW);
}

void LedDriver::toggle()
{
    if (state)
    {
        off();
    }
    else
    {
        on();
    }
}

bool LedDriver::isOn() const
{
    return state;
}
