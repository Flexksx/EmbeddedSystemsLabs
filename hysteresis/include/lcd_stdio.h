#ifndef LCD_STDIO_H
#define LCD_STDIO_H
#include <Arduino.h>
// Call once at startup to initialize the LCD for stdio usage
void setupStdioLcd(void);

// Optional helper to clear the entire display and move the cursor to (0,0)
void lcdClear(void);

// Optional helper to set the LCD cursor
void lcdSetCursor(uint8_t col, uint8_t row);

#endif // LCD_STDIO_H
