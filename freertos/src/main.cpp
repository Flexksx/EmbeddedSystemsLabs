#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "led_control.h"
#include "button_control.h"
#include "serial_stdio.h"
#include "task_button_led.h"
#include "task_sync.h"
#include "task_async.h"
#include "queue_manager.h"

TaskHandle_t buttonLedTaskHandle;
TaskHandle_t syncTaskHandle;
TaskHandle_t asyncTaskHandle;

void setup()
{
  Serial.begin(9600);
  init_stdio();

  printf("\n\n--- FreeRTOS Lab 2.2 - Modular Design ---\n");
  printf("System initialized and starting tasks...\n");

  setupLEDs();
  setupButton();

  if (!initializeSemaphore() || !initializeQueue())
  {
    printf("Error: Failed to initialize communication primitives\n");
    while (1)
      ;
  }

  // Create tasks
  // Task 1: Button LED (highest priority)
  xTaskCreate(ButtonLedTask, "ButtonLED", 128, NULL, 3, &buttonLedTaskHandle);

  // Task 2: Synchronous Task
  xTaskCreate(SyncTask, "SyncTask", 128, NULL, 3, &syncTaskHandle);

  // Task 3: Asynchronous Task
  xTaskCreate(AsyncTask, "AsyncTask", 128, NULL, 3, &asyncTaskHandle);

  vTaskStartScheduler();

  printf("Error: Not enough memory to start scheduler\n");
  while (1)
    ;
}

void loop()
{
}