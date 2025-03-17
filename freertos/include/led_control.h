#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

// Pin definitions
extern const int led1Pin;
extern const int led2Pin;

// Function prototypes
void setupLEDs();
void turnOnLED(int pin);
void turnOffLED(int pin);
void toggleLED(int pin);
void blinkLED(int pin, int times, int onTime, int offTime);

#endif