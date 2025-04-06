#ifndef JOYSTICK_H
#define JOYSTICK_H

// Data structure for the joystick
typedef struct
{
    int x;
    int y;
} JoystickState_t;

// Functions to read the joystick and classify its position
JoystickState_t readJoystickDriver();
const char *classifyX(int xVal);
const char *classifyY(int yVal);

#endif // JOYSTICK_H
