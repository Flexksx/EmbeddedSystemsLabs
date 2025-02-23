#include "serial_handler.h"

FILE serial_stdio;

void SerialHandler::begin(unsigned long baudRate)
{
    Serial.begin(baudRate);
    while (!Serial)
    {
    }
    setupStdio();
}

int SerialHandler::serialPutchar(char c, FILE *stream)
{
    Serial.write(c);
    return 0;
}

int SerialHandler::serialGetchar(FILE *stream)
{
    while (!Serial.available())
    {
    }
    return Serial.read();
}

void SerialHandler::setupStdio()
{
    fdev_setup_stream(&serial_stdio, serialPutchar, serialGetchar, _FDEV_SETUP_RW);
    stdout = &serial_stdio;
    stdin = &serial_stdio;
}

char *SerialHandler::readCommand()
{
    if (fgets(commandBuffer, MAX_COMMAND_LENGTH, stdin))
    {
        size_t len = strlen(commandBuffer);
        if (len > 0 && commandBuffer[len - 1] == '\n')
        {
            commandBuffer[len - 1] = '\0';
        }

        printf("Received command: %s\n", commandBuffer);

        while (Serial.available())
        {
            Serial.read();
        }

        return commandBuffer;
    }
    return nullptr;
}