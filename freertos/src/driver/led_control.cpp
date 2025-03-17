#include "led_control.h"
#include <Arduino_FreeRTOS.h>

const int led1Pin = 8;
const int led2Pin = 9;

void setupLEDs()
{
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
}

void turnOnLED(int pin)
{
  digitalWrite(pin, HIGH);
}

void turnOffLED(int pin)
{
  digitalWrite(pin, LOW);
}

void toggleLED(int pin)
{
  digitalWrite(pin, !digitalRead(pin));
}

void blinkLED(int pin, int times, int onTime, int offTime)
{
  for (int i = 0; i < times; i++)
  {
    turnOnLED(pin);
    vTaskDelay(pdMS_TO_TICKS(onTime));
    turnOffLED(pin);
    vTaskDelay(pdMS_TO_TICKS(offTime));
  }
}