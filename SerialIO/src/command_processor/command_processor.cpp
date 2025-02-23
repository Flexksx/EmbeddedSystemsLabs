#include "command_processor.h"
#include <string.h>
#include <stdio.h>

CommandProcessor::CommandProcessor(Led *led) : led(led) {}

void CommandProcessor::processCommand(const char *command)
{
    for (size_t i = 0; i < strlen(command); i++)
    {
        printf("[%c]", command[i]);
    }

    char cleanCommand[32];
    strncpy(cleanCommand, command, sizeof(cleanCommand) - 1);
    cleanCommand[sizeof(cleanCommand) - 1] = '\0';

    size_t len = strlen(cleanCommand);
    while (len > 0 && (cleanCommand[len - 1] == ' ' ||
                       cleanCommand[len - 1] == '\n' ||
                       cleanCommand[len - 1] == '\r'))
    {
        cleanCommand[--len] = '\0';
    }

    if (strcmp(cleanCommand, "led on") == 0)
    {
        led->setState(HIGH);
        printf("LED is on.\n");
    }
    else if (strcmp(cleanCommand, "led off") == 0)
    {
        led->setState(LOW);
        printf("LED is off.\n");
    }
    else
    {
        printf("Unrecognized command. Valid commands are: 'led on' or 'led off'.\n");
    }
}