#include "task_read_joystick.h"

#include "joystick_state.h"

#define JOY_Y_PIN A0
#define JOY_X_PIN A1

void taskReadJoystick(void *pvParameters)

{
    Serial.println("Joystick task is starting...");
    for (;;)
    {
        int xValue = analogRead(JOY_X_PIN);
        int yValue = analogRead(JOY_Y_PIN);
        Serial.print("X: ");
        Serial.print(xValue);
        Serial.print(", Y: ");
        Serial.println(yValue);
    }
}