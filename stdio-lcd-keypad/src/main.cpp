#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <stdio.h>  // for FILE
#include <stdarg.h> // for va_list, vsnprintf
#include "led/Led.h"
#include "password_controller/PasswordController.h"

// --------------- PIN DEFINITIONS & GLOBALS ---------------
#define GREEN_LED_PIN 8
#define RED_LED_PIN 9

// 4x4 keypad pins and layout
const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;

byte rowPins[KEYPAD_ROWS] = {5, 4, 3, 2};
byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};

char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

Led greenLed(GREEN_LED_PIN);
Led redLed(RED_LED_PIN);
PasswordController passwordController;

#define PASSCODE_LENGTH 4

String inputBuffer = "";

unsigned long ignoreUntil = 0;

enum SystemState
{
  NO_PASSWORD,             // user must set a 4-digit code
  LOCKED,                  // password is set; user can unlock or reset
  WAITING_FOR_UNLOCK_CODE, // user pressed '*' => gather 4 digits, press 'A' to check
  WAITING_FOR_RESET_CODE   // user pressed '#' => gather 4 digits, press 'A' to check
};

SystemState currentState = NO_PASSWORD;

// -----------------------------------------------------------------------------
// 1) Define a global pointer to the LCD, plus a function to write each character
//    This is used by fdev_setup_stream to make printf() output go to the LCD.
// -----------------------------------------------------------------------------

static LiquidCrystal_I2C *g_lcd = nullptr;

/**
 * Called whenever printf outputs a character.
 * We'll print it to the LCD. A '\n' toggles to the next LCD row (for a 16x2).
 */
static int lcdPutChar(char c, FILE *stream)
{
  static uint8_t currentRow = 0;
  static uint8_t currentCol = 0;

  if (c == '\n')
  {
    // Move to the next row, reset column
    currentRow = (uint8_t)((currentRow + 1) % 2); // only 2 rows
    currentCol = 0;
    g_lcd->setCursor(currentCol, currentRow);
  }
  else
  {
    g_lcd->print(c);
    currentCol++;
    // If we reach the end of the row, wrap automatically or ignore
    if (currentCol >= 16)
    {
      currentRow = (uint8_t)((currentRow + 1) % 2); // next row
      currentCol = 0;
      g_lcd->setCursor(currentCol, currentRow);
    }
  }
  return 0; // success
}

/**
 * Hook up our lcdPutChar function to the 'stdout' stream so that normal
 * 'printf()' calls will go to the LCD.
 */
void redirectStdoutToLCD(LiquidCrystal_I2C &lcdRef)
{
  static FILE lcdOut; // static so it remains valid

  g_lcd = &lcdRef;
  fdev_setup_stream(&lcdOut, lcdPutChar, NULL, _FDEV_SETUP_WRITE);

  // Make this stream the default stdout so that printf() uses it
  stdout = &lcdOut;
}

// --------------- HELPER FUNCTIONS ---------------
void printCurrentState(const char *prefix = nullptr)
{
  if (prefix)
  {
    Serial.print(prefix);
    Serial.print(" - ");
  }
  switch (currentState)
  {
  case NO_PASSWORD:
    Serial.println("State: NO_PASSWORD");
    break;
  case LOCKED:
    Serial.println("State: LOCKED");
    break;
  case WAITING_FOR_UNLOCK_CODE:
    Serial.println("State: WAITING_FOR_UNLOCK_CODE");
    break;
  case WAITING_FOR_RESET_CODE:
    Serial.println("State: WAITING_FOR_RESET_CODE");
    break;
  default:
    Serial.println("State: UNKNOWN");
    break;
  }
}

void resetInputBuffer(const char *line1 = nullptr)
{
  Serial.println("resetInputBuffer() called");
  inputBuffer = "";

  lcd.clear();
  lcd.setCursor(0, 0);

  if (line1)
  {
    printf("%s", line1);
    Serial.print("LCD line1: ");
    Serial.println(line1);
  }

  lcd.setCursor(0, 1);
}

void showMessage(const char *msg, unsigned long durationMs = 0)
{
  Serial.print("showMessage(): ");
  Serial.print(msg);
  Serial.print(", ignore for (ms): ");
  Serial.println(durationMs);

  lcd.clear();
  lcd.setCursor(0, 0);
  printf("%s", msg);

  if (durationMs > 0)
  {
    ignoreUntil = millis() + durationMs;
  }
}

void handleUserEnteredCode()
{
  Serial.println("handleUserEnteredCode() called");
  Serial.print("User entered: ");
  Serial.println(inputBuffer);

  switch (currentState)
  {
  case NO_PASSWORD:
    if (inputBuffer.length() == PASSCODE_LENGTH)
    {
      bool success = passwordController.setPasscode(inputBuffer.c_str());
      Serial.print("Setting code success: ");
      Serial.println(success ? "YES" : "NO");
      if (success)
      {
        showMessage("Code Set!", 1000);
        currentState = LOCKED;
      }
      else
      {
        showMessage("Invalid Code!", 1000);
      }
    }
    else
    {
      showMessage("Need 4 digits!", 1000);
    }
    break;

  case WAITING_FOR_UNLOCK_CODE:
    if (inputBuffer.length() == PASSCODE_LENGTH &&
        passwordController.matchPasscode(inputBuffer.c_str()))
    {
      Serial.println("Unlock code correct!");
      greenLed.turnOn();
      redLed.turnOff();
      showMessage("Correct", 1000);
    }
    else
    {
      Serial.println("Unlock code wrong!");
      redLed.turnOn();
      greenLed.turnOff();
      showMessage("Wrong", 1000);
    }
    currentState = LOCKED;
    break;

  case WAITING_FOR_RESET_CODE:
    if (inputBuffer.length() == PASSCODE_LENGTH &&
        passwordController.matchPasscode(inputBuffer.c_str()))
    {
      Serial.println("Reset code correct!");
      passwordController.deletePasscode();
      showMessage("Code Reset", 1000);
      currentState = NO_PASSWORD;
    }
    else
    {
      Serial.println("Reset code wrong!");
      redLed.turnOn();
      greenLed.turnOff();
      showMessage("Wrong", 1000);
      currentState = LOCKED;
    }
    break;

  case LOCKED:
    Serial.println("handleUserEnteredCode() called in LOCKED unexpectedly.");
    showMessage("Press '*' or '#'", 1000);
    break;
  }

  printCurrentState("After handleUserEnteredCode");
  inputBuffer = "";
}

// --------------- SETUP & LOOP ---------------
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }
  Serial.println("Setup started...");

  lcd.init();
  lcd.backlight();

  redirectStdoutToLCD(lcd);

  greenLed.turnOff();
  redLed.turnOff();

  passwordController.deletePasscode();
  currentState = NO_PASSWORD;
  Serial.println("Password deleted, state set to NO_PASSWORD.");

  resetInputBuffer("Set 4-digit code");

  printf("Press A to save");
  Serial.println("Setup complete. Prompting for new passcode...");
  printCurrentState();
}

void loop()
{
  if (millis() < ignoreUntil)
  {
    return;
  }

  greenLed.turnOff();
  redLed.turnOff();

  char key = keypad.getKey();
  if (key == NO_KEY)
    return;

  Serial.print("Key pressed: ");
  Serial.println(key);

  if (key == 'A')
  {
    handleUserEnteredCode();
    return;
  }

  if (key == '*')
  {
    if (currentState == LOCKED)
    {
      Serial.println("User pressed '*': switching to WAITING_FOR_UNLOCK_CODE");
      resetInputBuffer("Enter code:");
      lcd.setCursor(0, 1);
      printf("Press A to unlock");
      currentState = WAITING_FOR_UNLOCK_CODE;
      printCurrentState();
    }
    else
    {
      Serial.println("Ignoring '*': current state not LOCKED.");
    }
    return;
  }

  if (key == '#')
  {
    if (currentState == LOCKED)
    {
      Serial.println("User pressed '#': switching to WAITING_FOR_RESET_CODE");
      resetInputBuffer("Enter old code:");
      lcd.setCursor(0, 1);
      printf("Press A to reset");
      currentState = WAITING_FOR_RESET_CODE;
      printCurrentState();
    }
    else
    {
      Serial.println("Ignoring '#': current state not LOCKED.");
    }
    return;
  }

  // If it's a digit:
  if (key >= '0' && key <= '9')
  {
    if (inputBuffer.length() < PASSCODE_LENGTH)
    {
      inputBuffer += key;
      Serial.print("inputBuffer updated: ");
      Serial.println(inputBuffer);

      // Manually place an asterisk at the right position (second row)
      lcd.setCursor(inputBuffer.length() - 1, 1);
      printf("*");
    }
    else
    {
      Serial.println("Already have 4 digits, ignoring extra digit.");
    }
  }
}
