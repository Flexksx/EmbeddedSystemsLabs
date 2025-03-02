#ifndef LED_BULB_H
#define LED_BULB_H

#include <Arduino.h>

class Led
{
private:
  int pin;
  int current_state;

public:
  Led(int pin);

  uint8_t getState();

  void setState(uint8_t state);

  void toggle();

  void turnOff();

  void turnOn();
};

#endif
