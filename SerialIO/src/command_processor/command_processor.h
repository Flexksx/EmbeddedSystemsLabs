#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <led/led.h>

class CommandProcessor
{
public:
    explicit CommandProcessor(Led *led);
    void processCommand(const char *command);

private:
    Led *led;
};

#endif