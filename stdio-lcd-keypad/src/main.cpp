#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

int myFunction(int, int);

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLUMNS = 4;
byte rowPins[KEYPAD_ROWS] = {9, 8, 7, 6};
byte colPins[KEYPAD_COLUMNS] = {5, 4, 3, 2};
char keys[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLUMNS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("DON POLLO");
}

void loop()
{
}

int myFunction(int x, int y)
{
  return x + y;
}