#include "lcd_driver.h"
#include "joystick_state.h"
#include "task_display_state.h"
#include "lcd_driver.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>

#define DISPLAY_UPDATE_MS 250

void taskUpdateDisplay(void *pvParameters)
{
    Serial.println("Log: Display Task Started.");
    clearLcd();
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(DISPLAY_UPDATE_MS);
    int localX = 0;
    int localY = 0;
    xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        Serial.println("Log: Display Update Task");

        if (takeMutex(100) == pdTRUE)
        {
            Serial.println("Log: Display Task got mutex.");
            localX = getX();
            localY = getY();
            giveMutex();

            lcd_printf(0, 0, "H:%d", localX);
            lcd_printf(0, 1, "V:%d", localY);

            Serial.print("Log: Display Update - H: ");
            Serial.print(localX);
            Serial.print(" | V: ");
            Serial.println(localY);
        }
        else
        {
            Serial.println("Log: Error - Display Task couldn't get mutex!");
            lcd_printf(0, 0, "MUTEX ERROR");
            lcd_printf(0, 1, "Display Task");
        }
    }
}