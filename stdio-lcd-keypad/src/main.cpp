#include <Arduino.h>
#include <service/keypad_service/KeypadService.h>
#include <service/lcd_service/LcdService.h>
#include <service/password_service/PasswordService.h>
#include <driver/led/Led.h>

#define GREEN_LED_PIN 8
#define RED_LED_PIN 9

Led greenLed(GREEN_LED_PIN);
Led redLed(RED_LED_PIN);
PasswordService passwordService;
KeypadService keypadService;
LcdService lcdService;

#define PASSCODE_LENGTH 4
char inputBuffer[PASSCODE_LENGTH + 1];

void setNewCode()
{
    passwordService.deletePasscode();
    lcdService.clear();
    printf("Enter new \n");
    printf("4-digit code:");

    scanf("%4s", inputBuffer);

    if (!passwordService.setPasscode(inputBuffer))
    {
        lcdService.clear();
        printf("Code has to\n");
        printf("be 4 digits");
        return;
    }
    lcdService.clear();
    printf("New code set!\n");
}

void checkCode()
{
    if (!passwordService.hasPasscode())
    {
        lcdService.clear();
        printf("No passcode set.\n");
        return;
    }
    lcdService.clear();
    printf("Enter code\n");
    printf("to check: ");
    scanf("%4s", inputBuffer);

    if (passwordService.matchPasscode(inputBuffer))
    {
        lcdService.clear();
        printf("Correct!\n");
        greenLed.turnOn();
        redLed.turnOff();
    }
    else
    {
        lcdService.clear();
        printf("Incorrect!\n");
        redLed.turnOn();
        greenLed.turnOff();
    }

    delay(2000);
    greenLed.turnOff();
    redLed.turnOff();
}

void setup()
{
    Serial.begin(9600);

    keypadService.setupStdioKeypad();
    lcdService.setupStdioLcd();

    greenLed.turnOff();
    redLed.turnOff();

    passwordService.deletePasscode();
    lcdService.clear();
    printf("'#' - set new\n");
}

void loop()
{
    char action;
    scanf("%c", &action);

    if (action == '#')
    {
        setNewCode();
    }
    else if (action == '*')
    {
        checkCode();
    }
    else
    {
        lcdService.clear();
        printf("\nInvalid key.\n");
    }
    lcdService.clear();
    printf("# - reset code\n");
    printf("* - check code");
}
