#ifndef TASK_IDLE_H
#define TASK_IDLE_H

#include <Arduino.h>
#include "LedDriver.h"

/**
 * Prints system status every second:
 *  - LED1 state
 *  - LED2 state
 *  - Current blink interval
 */
class TaskIdle
{
private:
    LedDriver &led1;
    LedDriver &led2;
    int &blinkIntervalRef;
    bool &led2StateRef; // track actual LED2 ON/OFF

    unsigned long lastReportTime;
    const unsigned long reportInterval;

public:
    TaskIdle(LedDriver &led1Ref, LedDriver &led2Ref, int &intervalRef, bool &led2State);
    void runTask();
};

#endif
