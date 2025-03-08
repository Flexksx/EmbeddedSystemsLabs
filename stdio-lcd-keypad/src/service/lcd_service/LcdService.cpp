#include "LcdService.h"

LcdService *LcdService::instance = nullptr;

LcdService::LcdService() : lcd(0x27, 16, 2)
{
    instance = this;
}

void LcdService::print(const char *message)
{
    lcd.print(message);
}

void LcdService::clear()
{
    lcd.clear();
}

int LcdService::lcdPutChar(char c, FILE *stream)
{
    if (instance)
    {
        if (c == '\n')
        {
            instance->lcd.setCursor(0, 1);
        }
        else
        {
            instance->lcd.write(c);
        }
    }
    return c;
}

void LcdService::setupStdioLcd()
{
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    fdevopen(lcdPutChar, NULL);
}
