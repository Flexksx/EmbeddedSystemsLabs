#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>

void setupLCD();

void taskUpdateDisplay(void *pvParameters);

#endif // LCD_DISPLAY_H