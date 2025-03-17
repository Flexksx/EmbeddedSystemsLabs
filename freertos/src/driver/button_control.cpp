#include "button_control.h"
#include <Arduino_FreeRTOS.h>

// Pin definitions
const int buttonPin = 7; // Button input pin

void setupButton()
{
  pinMode(buttonPin, INPUT_PULLUP);
}

bool isButtonPressed()
{
  // Button is pressed when it reads LOW (INPUT_PULLUP)
  if (digitalRead(buttonPin) == LOW)
  {
    // Simple debounce
    vTaskDelay(pdMS_TO_TICKS(50));
    return (digitalRead(buttonPin) == LOW);
  }
  return false;
}

void waitForButtonRelease()
{
  while (digitalRead(buttonPin) == LOW)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}