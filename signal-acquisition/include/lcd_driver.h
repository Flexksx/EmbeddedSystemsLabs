#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void setupLCD();
void initializeDisplayToStdio();
void lcd_printf(uint8_t col, uint8_t row, const char *format, ...);
int lcd_putchar(char c, FILE *stream);
void clearLcd();
void lcd_puts(const char *s, FILE *stream);
#endif // LCD_DRIVER_H
