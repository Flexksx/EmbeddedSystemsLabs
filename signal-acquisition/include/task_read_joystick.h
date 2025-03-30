#ifndef JOYSTICK_READ_TASK_H
#define JOYSTICK_READ_TASK_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "joystick_state.h"

// Task to read the joystick and update the shared state
void taskReadJoystick(void *pvParameters);

#endif // JOYSTICK_READ_TASK_H
