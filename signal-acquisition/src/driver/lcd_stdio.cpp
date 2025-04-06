#include "lcd_stdio.h"
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------------------------------------------------------------------
// Create a private LCD instance (16x2). Change address or size if needed
// ---------------------------------------------------------------------
static LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------------------------------------------------------------
// This function is used by printf() to output characters to the LCD
// We handle '\n' by moving to line 1, but you can be more sophisticated.
// ---------------------------------------------------------------------
static int lcdPutChar(char c, FILE *stream)
{
    if (c == '\n')
    {
        // Move to second line
        lcd.setCursor(0, 1);
    }
    else
    {
        lcd.write(c);
    }
    return 0; // success
}

// ---------------------------------------------------------------------
// Public function: Setup the LCD for stdio usage
// Creates a custom stream for stdout
// ---------------------------------------------------------------------
void setupStdioLcd(void)
{
    // Initialize hardware
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);

    // Create a FILE stream to use for stdout
    static FILE lcdOut;
    fdev_setup_stream(&lcdOut, lcdPutChar, NULL, _FDEV_SETUP_WRITE);

    // Redirect stdout (and optionally stderr) to our lcdOut
    stdout = &lcdOut;
    // stderr = &lcdOut;  // if desired

    // You can optionally print an initial message
    // printf("LCD ready\n");
}

// ---------------------------------------------------------------------
// Public function: Clear the LCD, cursor to (0,0)
// ---------------------------------------------------------------------
void lcdClear(void)
{
    lcd.clear();
    lcd.setCursor(0, 0);
}

// ---------------------------------------------------------------------
// Public function: Set the LCD cursor
// ---------------------------------------------------------------------
void lcdSetCursor(uint8_t col, uint8_t row)
{
    lcd.setCursor(col, row);
}
