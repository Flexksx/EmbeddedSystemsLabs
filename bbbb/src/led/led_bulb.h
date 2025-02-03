#ifndef LED_BULB_H
#define LED_BULB_H

#include <Arduino.h>

class LedBulb
{
private:
  int pin;
  int current_state;

public:
  LedBulb(int pin);

  uint8_t getState();

  void setState(uint8_t state);

  void toggle();
};

#endif
