#include "lcd_stdio.h"
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(0x27, 16, 2);

static int lcdPutChar(char c, FILE *stream)
{
    if (c == '\n')
    {
        lcd.setCursor(0, 1);
    }
    else
    {
        lcd.write(c);
    }
    return 0;
}

void setupStdioLcd(void)
{
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);

    static FILE lcdOut;
    fdev_setup_stream(&lcdOut, lcdPutChar, NULL, _FDEV_SETUP_WRITE);

    stdout = &lcdOut;
}

void lcdClear(void)
{
    lcd.clear();
    lcd.setCursor(0, 0);
}

void lcdSetCursor(uint8_t col, uint8_t row)
{
    lcd.setCursor(col, row);
}
