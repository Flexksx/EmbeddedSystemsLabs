#include "joystick_state.h"

joystick_state currentJoystickState = {512, 512};

bool initializeJoystickState()
{
    currentJoystickState = {512, 512};
    return true;
}

bool setState(joystick_state state)
{
    currentJoystickState = state;
    return true;
}

joystick_state getState()
{
    return currentJoystickState;
}

bool giveMutex()
{
    xSemaphoreGive(joystickStateMutex);
    return true;
}

bool takeMutex(TickType_t timeout)

{

    return xSemaphoreTake(joystickStateMutex, timeout);
}

int getX()
{
    return currentJoystickState.x;
}

int getY()
{
    return currentJoystickState.y;
}
