#include "TaskIdle.h"

TaskIdle::TaskIdle(LedDriver &led1Ref,
                   LedDriver &led2Ref,
                   int &intervalRef,
                   bool &led2State)
    : led1(led1Ref), led2(led2Ref),
      blinkIntervalRef(intervalRef),
      led2StateRef(led2State),
      lastReportTime(0),
      reportInterval(1000) // print once per second
{
}

void TaskIdle::runTask()
{
    unsigned long now = millis();
    if (now - lastReportTime >= reportInterval)
    {
        lastReportTime = now;

        printf("=== SYSTEM STATUS ===");
        Serial.print("LED1: ");
        printf(led1.isOn() ? "ON" : "OFF");

        Serial.print("LED2: ");
        printf(led2StateRef ? "ON" : "OFF");

        Serial.print("Blink Interval: ");
        Serial.print(blinkIntervalRef);
        printf(" ms");
        printf("=====================");
    }
}
