#ifndef KEYPAD_SERVICE_H
#define KEYPAD_SERVICE_H

#include <Arduino.h>
#include <Keypad.h>
#include <stdio.h>

class KeypadService
{
private:
    static KeypadService *instance;

    static const byte ROWS = 4;
    static const byte COLS = 4;
    char keys[ROWS][COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};

    byte rowPins[ROWS] = {5, 4, 3, 2};
    byte colPins[COLS] = {A3, A2, A1, A0};

    Keypad keypad;

    static int keypadRead(FILE *stream);

public:
    KeypadService();

    void setupStdioKeypad();
};

#endif
