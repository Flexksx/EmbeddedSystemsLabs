#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>
#include <stdio.h>

class SerialHandler
{
public:
    void begin(unsigned long baudRate);
    char *readCommand();

private:
    static constexpr size_t MAX_COMMAND_LENGTH = 32;
    char commandBuffer[MAX_COMMAND_LENGTH];

    static int serialPutchar(char c, FILE *stream);
    static int serialGetchar(FILE *stream);
    void setupStdio();
};

#endif