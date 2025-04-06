#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>
#include "read_joystick_task.h"
#include "joystick_driver.h"
#include "lcd_stdio.h"

extern JoystickState_t gJoystick;
extern SemaphoreHandle_t xJoystickMutex;

void vJoystickTask(void *pvParameters)
{
    (void)pvParameters;

    for (;;)
    {
        // Acquire the mutex
        if (xSemaphoreTake(xJoystickMutex, portMAX_DELAY) == pdTRUE)
        {
            gJoystick = readJoystickDriver();
            xSemaphoreGive(xJoystickMutex);
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // sample every 100 ms
    }
}
