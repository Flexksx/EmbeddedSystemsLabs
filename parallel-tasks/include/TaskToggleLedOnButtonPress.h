#ifndef TASK_TOGGLE_LED_ON_BUTTON_PRESS_H
#define TASK_TOGGLE_LED_ON_BUTTON_PRESS_H

#include <Arduino.h>
#include "ButtonDriver.h"
#include "LedDriver.h"

class TaskToggleLedOnButtonPress
{
private:
    ButtonDriver &button;
    LedDriver &led1;

public:
    TaskToggleLedOnButtonPress(ButtonDriver &btn, LedDriver &ledRef);
    void runTask();
};

#endif
