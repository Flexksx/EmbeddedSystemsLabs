#ifndef TASK_CHANGE_LED_BLINK_INTERVAL_H
#define TASK_CHANGE_LED_BLINK_INTERVAL_H

#include <Arduino.h>
#include "ButtonDriver.h"

/**
 * Adjusts a shared blinkInterval by ±200 ms
 * using two buttons (Up / Down).
 */
class TaskChangeLedBlinkInterval
{
private:
    ButtonDriver &btnUp;
    ButtonDriver &btnDown;
    int &blinkIntervalRef; // reference to a shared variable

public:
    TaskChangeLedBlinkInterval(ButtonDriver &up, ButtonDriver &down, int &blinkRef);
    void runTask();
};

#endif
