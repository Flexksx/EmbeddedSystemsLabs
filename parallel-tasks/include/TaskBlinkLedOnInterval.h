#ifndef TASK_BLINK_LED_ON_INTERVAL_H
#define TASK_BLINK_LED_ON_INTERVAL_H

#include <Arduino.h>
#include "LedDriver.h"

/**
 * Blinks LED2 only if LED1 is OFF.
 * Tied to a shared blinkInterval (in ms).
 * Also updates a bool &led2State to reflect ON/OFF.
 */
class TaskBlinkLedOnInterval
{
private:
    LedDriver &led2;
    LedDriver &led1;
    int &blinkInterval;
    bool &led2State;
    unsigned long prevTime;

public:
    TaskBlinkLedOnInterval(LedDriver &led2Ref, LedDriver &led1Ref, int &bInterval, bool &led2St);
    void runTask();
};

#endif
