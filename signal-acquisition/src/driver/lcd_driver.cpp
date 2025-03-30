#include "lcd_driver.h"
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setupLCD()
{
    Wire.begin();
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("System Starting");
    Serial.println("Log: LCD Initialized.");
}

void clearLcd()
{
    lcd.clear();
}
void lcd_printf(uint8_t col, uint8_t row, const char *format, ...)
{
    char buffer[LCD_COLS + 1];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, LCD_COLS + 1, format, args);
    va_end(args);

    lcd.setCursor(col, row);
    lcd.print(buffer);
}

int lcd_putchar(char c, FILE *stream)
{
    lcd.write(c);
    return c;
}

static FILE lcd_out;

void initializeDisplayToStdio()
{
    fdev_setup_stream(&lcd_out, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &lcd_out;
}