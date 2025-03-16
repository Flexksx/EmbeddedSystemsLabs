#include "TaskChangeLedBlinkInterval.h"

TaskChangeLedBlinkInterval::TaskChangeLedBlinkInterval(ButtonDriver &up,
                                                       ButtonDriver &down,
                                                       int &blinkRef)
    : btnUp(up), btnDown(down), blinkIntervalRef(blinkRef)
{
}

void TaskChangeLedBlinkInterval::runTask()
{
    btnUp.update();
    if (btnUp.wasJustPressed())
    {
        blinkIntervalRef += 200;
        Serial.print("Blink interval increased => ");
        Serial.print(blinkIntervalRef);
        Serial.println(" ms");
    }

    // Check Down button
    btnDown.update();
    if (btnDown.wasJustPressed())
    {
        if (blinkIntervalRef > 200)
        {
            blinkIntervalRef -= 200;
        }
        Serial.print("Blink interval decreased => ");
        Serial.print(blinkIntervalRef);
        Serial.println(" ms");
    }
}
