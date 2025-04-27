#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

class Button
{
private:
    int pin;
    bool lastState;
    bool buttonPressed = false;
    unsigned long lastDebounceTime;

public:
    Button(int pin);
    void setup();
    bool isClicked();
    bool isClickedDB();
};

#endif