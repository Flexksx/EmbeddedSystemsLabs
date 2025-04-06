#include <Arduino.h>
#include "joystick_driver.h"

// Thresholds and logic for classification
#define JOY_CENTER 512
#define JOY_FULL_MARGIN 50
#define JOY_DEADBAND 80

// readJoystickDriver() reads analog pins and returns a JoystickState_t
// Adjust pins as needed
JoystickState_t readJoystickDriver()
{
    JoystickState_t state;
    // Example: invert X reading, keep Y normal
    state.x = 1023 - analogRead(A1);
    state.y = analogRead(A0);
    return state;
}

// classifyX() interprets the integer 'xVal' as LEFT / RIGHT / FULL, or CENTER
const char *classifyX(int xVal)
{
    if (xVal < JOY_FULL_MARGIN)
    {
        return "FULL LEFT";
    }
    else if (xVal < (JOY_CENTER - JOY_DEADBAND))
    {
        return "LEFT";
    }
    else if (xVal > (1023 - JOY_FULL_MARGIN))
    {
        return "FULL RIGHT";
    }
    else if (xVal > (JOY_CENTER + JOY_DEADBAND))
    {
        return "RIGHT";
    }
    else
    {
        return "CENTER";
    }
}

// classifyY() interprets yVal as UP / DOWN / FULL, or CENTER
const char *classifyY(int yVal)
{
    if (yVal < JOY_FULL_MARGIN)
    {
        return "FULL DOWN";
    }
    else if (yVal < (JOY_CENTER - JOY_DEADBAND))
    {
        return "DOWN";
    }
    else if (yVal > (1023 - JOY_FULL_MARGIN))
    {
        return "FULL UP";
    }
    else if (yVal > (JOY_CENTER + JOY_DEADBAND))
    {
        return "UP";
    }
    else
    {
        return "CENTER";
    }
}
