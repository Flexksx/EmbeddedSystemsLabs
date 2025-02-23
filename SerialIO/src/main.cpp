#include <Arduino.h>
#include <stdio.h>
#include "./serial_handler/serial_handler.h"
#include "./command_processor/command_processor.h"
#include "./led/led.h"

constexpr uint8_t LED_PIN = 13;
Led led(LED_PIN);
SerialHandler serialHandler;
CommandProcessor cmdProcessor(&led);

void setup()
{
  serialHandler.begin(9600);
  printf("LED Control app - Available commands: 'led on' or 'led off'\n");
}

void loop()
{
  if (char *command = serialHandler.readCommand())
  {
    cmdProcessor.processCommand(command);
  }
}