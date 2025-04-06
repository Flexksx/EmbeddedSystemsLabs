#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>
#include "display_task.h"
#include "joystick_driver.h"
#include "lcd_stdio.h"

// External references to your joystick data and mutex
extern JoystickState_t gJoystick;
extern SemaphoreHandle_t xJoystickMutex;

// The display task
void vDisplayTask(void *pvParams)
{
    (void)pvParams;

    // Prepare the LCD for stdio output
    setupStdioLcd();

    // Initial message (optional)
    printf("Joystick Demo\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    lcdClear();

    for (;;)
    {
        JoystickState_t localJoy;

        // Acquire the mutex to read the global joystick data
        if (xSemaphoreTake(xJoystickMutex, pdMS_TO_TICKS(50)) == pdTRUE)
        {
            localJoy = gJoystick;
            xSemaphoreGive(xJoystickMutex);
        }
        else
        {
            // Fallback if mutex not obtained quickly
            localJoy.x = 512; // center
            localJoy.y = 512; // center
        }

        // Use classifyX() and classifyY() from your driver to get direction text
        const char *xLabel = classifyX(localJoy.x);
        const char *yLabel = classifyY(localJoy.y);

        // Clear LCD, then print classification. The '\n' moves to second line.
        lcdClear();
        printf("X=%s\nY=%s", xLabel, yLabel);

        // Repeat every second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
