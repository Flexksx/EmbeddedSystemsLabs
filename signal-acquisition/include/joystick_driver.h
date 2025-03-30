#ifndef JOYSTICK_DRIVER_H
#define JOYSTICK_DRIVER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

int getX(int JOY_H_PIN);
int getY(int JOY_V_PIN);

#endif // JOYSTICK_DRIVER_H