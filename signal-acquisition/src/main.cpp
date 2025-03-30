#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "task_read_joystick.h"
#include "joystick_state.h"
#include "task_display_state.h"

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Setup");

  if (!initializeJoystickState())
  {
    Serial.println("Error initializing joystick state");
  }
  else
  {
    Serial.println("Joystick state initialized");
  }

  BaseType_t rc = xTaskCreate(taskReadJoystick, "ReadJoystickState", 128, NULL, 1, NULL);
  if (rc == pdPASS)
  {
    Serial.println("Task created OK");
    vTaskStartScheduler();
  }
  else
  {
    Serial.println("Task create FAIL");
  }

  BaseType_t rc2 = xTaskCreate(taskUpdateDisplay, "UpdateDisplay", 128, NULL, 1, NULL);
  if (rc2 == pdPASS)
  {
    Serial.println("Task created OK");
    vTaskStartScheduler();
  }
  else
  {
    Serial.println("Task create FAIL");
  }

  Serial.println("Scheduler didn't start");
}

void loop() {}
