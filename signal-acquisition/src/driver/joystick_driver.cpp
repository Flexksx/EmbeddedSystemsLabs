#include <joystick_driver.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define DEBOUNCE_DELAY_MS 10
int getX(int JOY_H_PIN)
{
    vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_DELAY_MS));
    return analogRead(JOY_H_PIN);
}

int getY(int JOY_V_PIN)
{
    vTaskDelay(pdMS_TO_TICKS(DEBOUNCE_DELAY_MS));
    return analogRead(JOY_V_PIN);
}
