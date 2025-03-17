#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

#include <Arduino.h>

// Pin definitions
extern const int buttonPin;

// Function prototypes
void setupButton();
bool isButtonPressed();
void waitForButtonRelease();

#endif