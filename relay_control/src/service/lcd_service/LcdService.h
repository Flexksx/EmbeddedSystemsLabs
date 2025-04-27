#ifndef LCD_SERVICE_H
#define LCD_SERVICE_H

#include <Arduino.h>
#include <stdio.h>
#include <LiquidCrystal_I2C.h>

class LcdService
{
private:
    static LcdService *instance;
    LiquidCrystal_I2C lcd;
    int cursorCol, cursorRow;

    static int lcdPutChar(char c, FILE *stream);

public:
    LcdService();
    void setupStdioLcd();
    void print(const char *message);
    void clear();
};

#endif
