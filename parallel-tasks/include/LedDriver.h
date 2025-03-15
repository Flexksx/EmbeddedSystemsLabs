#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Arduino.h>

class LedDriver
{
private:
    uint8_t pin;
    bool state; // true if ON, false if OFF

public:
    explicit LedDriver(uint8_t pinNumber);
    void begin();
    void on();
    void off();
    void toggle();
    bool isOn() const;
};

#endif
