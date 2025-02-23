#include <Arduino.h>
#include <led/led_bulb.h>

#define BUILT_IN_LED 13
#define BUTTON_PIN 21

int buttonState = LOW;
int lastButtonState = LOW;
int ledState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

Led bulb = Led(BUILT_IN_LED);

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUILT_IN_LED, OUTPUT);
}

void loop()
{
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading == HIGH && buttonState == LOW)
    {
      bulb.toggle();
    }
  }

  buttonState = reading;
  lastButtonState = reading;

  delay(10);
}
