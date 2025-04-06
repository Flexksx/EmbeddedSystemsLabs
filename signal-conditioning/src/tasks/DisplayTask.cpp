#include "DisplayTask.h"
#include "lcd_stdio.h"
#include <stdio.h>

extern float gFilteredLux;
extern SemaphoreHandle_t xSensorDataMutex;

void vDisplayTask(void *pvParameters)
{
    setupStdioLcd();

    const TickType_t xDelay = pdMS_TO_TICKS(1000);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        float luxVal = 0.0f;

        if (xSemaphoreTake(xSensorDataMutex, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            luxVal = gFilteredLux;
            xSemaphoreGive(xSensorDataMutex);
        }

        lcdClear();

        printf("Lux: %.2f\n", luxVal);

        vTaskDelayUntil(&xLastWakeTime, xDelay);
    }
}
