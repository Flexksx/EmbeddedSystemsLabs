
#include "SerialIo.h"
#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 100

int SerialIo::serial_putchar(char c, FILE *f)
{
    Serial.write(c);
    return 0;
}

int SerialIo::serial_getchar(FILE *f)
{
    while (Serial.available() <= 0)
    {
    }
    return Serial.read();
}

void SerialIo::init()
{
    static FILE *serial_stream = fdevopen(&serial_putchar, &serial_getchar);
    stdin = serial_stream;
    stdout = serial_stream;
}

void SerialIo::trim(char *str)
{
    int i = strlen(str) - 1;
    while (i >= 0 && isspace((unsigned char)str[i]))
    {
        str[i--] = '\0';
    }
    char *start = str;
    while (isspace((unsigned char)*start))
    {
        start++;
    }
    if (start != str)
    {
        memmove(str, start, strlen(start) + 1);
    }
}

char *SerialIo::input()
{
    static char input[MAX_INPUT];
    int i = 0;
    char c;

    while (scanf("%c", &c) != EOF && c != '\n' && c != '\r' && i < (MAX_INPUT - 1))
    {
        if (c == '\b' && i > 0)
        {
            printf("\b \b");
            fflush(stdout);
            i--;
        }
        else if (c != '\b' && c != '\r')
        {
            printf("%c", c);
            fflush(stdout);
            input[i++] = c;
        }
    }

    input[i] = '\0';
    trim(input);

    // send CR+LF so the next printf starts at column 0
    printf("\r\n");
    fflush(stdout);

    return input;
}
