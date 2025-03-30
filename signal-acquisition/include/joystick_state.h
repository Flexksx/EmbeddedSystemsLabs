#ifndef JOYSTICK_STATE_H
#define JOYSTICK_STATE_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

extern SemaphoreHandle_t joystickStateMutex = xSemaphoreCreateMutex();

struct joystick_state
{
    int x;
    int y;
};

bool setState(joystick_state state);
joystick_state getState();
bool initializeJoystickState();
bool giveMutex();
bool takeMutex(TickType_t timeout);
int getX();
int getY();

#endif // JOYSTICK_STATE_H
