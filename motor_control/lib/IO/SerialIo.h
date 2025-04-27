#ifndef SERIAL_IO_H
#define SERIAL_IO_H
#include <Arduino.h>
#include <stdio.h>

class SerialIo
{
public:
    static char *input();
    static void init();
    static void trim(char *str);

private:
    static int serial_putchar(char c, FILE *f);
    static int serial_getchar(FILE *f);
};

#endif // SERIAL_IO_H