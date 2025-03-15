#include "TaskToggleLedOnButtonPress.h"

TaskToggleLedOnButtonPress::TaskToggleLedOnButtonPress(ButtonDriver &btn, LedDriver &ledRef)
    : button(btn), led1(ledRef)
{
}

void TaskToggleLedOnButtonPress::runTask()
{
    button.update();
    if (button.wasJustPressed())
    {
        led1.toggle();
        Serial.print("LED1 toggled => ");
        Serial.println(led1.isOn() ? "ON" : "OFF");
    }
}
