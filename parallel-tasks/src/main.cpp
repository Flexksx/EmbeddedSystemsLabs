#include <Arduino.h>

// Drivers
#include "ButtonDriver.h"
#include "LedDriver.h"

// Task classes
#include "TaskToggleLedOnButtonPress.h"
#include "TaskChangeLedBlinkInterval.h"
#include "TaskBlinkLedOnInterval.h"
#include "TaskIdle.h"

// Pin assignments
constexpr uint8_t PIN_LED1 = 13;
constexpr uint8_t PIN_LED2 = 12;
constexpr uint8_t PIN_BUTTON_TOGGLE = 11;
constexpr uint8_t PIN_BUTTON_UP = 10;
constexpr uint8_t PIN_BUTTON_DOWN = 9;

// Driver objects
ButtonDriver buttonToggle(PIN_BUTTON_TOGGLE);
LedDriver led1(PIN_LED1);
ButtonDriver buttonUp(PIN_BUTTON_UP);
ButtonDriver buttonDown(PIN_BUTTON_DOWN);
LedDriver led2(PIN_LED2);

static int g_blinkInterval = 500;
static bool g_led2State = false;

// Task objects
TaskToggleLedOnButtonPress taskToggle(buttonToggle, led1);
TaskChangeLedBlinkInterval taskChangeInterval(buttonUp, buttonDown, g_blinkInterval);
TaskBlinkLedOnInterval taskBlink(led2, led1, g_blinkInterval, g_led2State);
TaskIdle taskIdle(led1, led2, g_blinkInterval, g_led2State);

void setup()
{
  Serial.begin(9600);

  // Initialize drivers
  buttonToggle.begin();
  buttonUp.begin();
  buttonDown.begin();
  led1.begin();
  led2.begin();

  Serial.println("System startup with separate tasks in separate files...");
  Serial.println("Press button on pin 11 to toggle LED1.");
  Serial.println("Use buttons on pins 10 (UP) & 9 (DOWN) to change blink interval.");
}

void loop()
{
  // Non-preemptive round-robin calls
  taskToggle.runTask();         // Toggle LED1 if button pressed
  taskBlink.runTask();          // Blink LED2 if LED1 is off
  taskChangeInterval.runTask(); // Up/Down button => change blinkInterval
  taskIdle.runTask();           // Print system status occasionally

  // Slow down the loo a bit
  delay(10);
}
