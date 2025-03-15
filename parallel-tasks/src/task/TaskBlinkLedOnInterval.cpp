#include "TaskBlinkLedOnInterval.h"

TaskBlinkLedOnInterval::TaskBlinkLedOnInterval(LedDriver &led2Ref,
                                               LedDriver &led1Ref,
                                               int &bInterval,
                                               bool &led2St)
    : led2(led2Ref), led1(led1Ref),
      blinkInterval(bInterval),
      led2State(led2St),
      prevTime(0)
{
    // Make sure we start with LED2 in the off state
    led2State = false;
}

void TaskBlinkLedOnInterval::runTask()
{
    if (!led1.isOn())
    {
        unsigned long now = millis();
        if (now - prevTime >= (unsigned long)blinkInterval)
        {
            prevTime = now;
            led2State = !led2State;
            if (led2State)
            {
                led2.on();
            }
            else
            {
                led2.off();
            }
        }
    }
    else
    {
        led2.off();
        led2State = false;
    }
}
