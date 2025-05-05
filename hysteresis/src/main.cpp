#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include "read_joystick_task.h"
#include "display_task.h"

#include "joystick_driver.h"

JoystickState_t gJoystick;
SemaphoreHandle_t xJoystickMutex = NULL;

void setup()
{
  // Setup pins
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  xJoystickMutex = xSemaphoreCreateMutex();
  if (xJoystickMutex == NULL)
  {
    while (1)
    {
    }
  }

  xTaskCreate(vJoystickTask, "JoyTask", 128, NULL, 2, NULL);
  xTaskCreate(vDisplayTask, "DispTask", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop()
{
  // Unused under FreeRTOS
  for (;;)
  {
  }
}
