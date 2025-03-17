#include "task_button_led.h"
#include "button_control.h"
#include "led_control.h"
#include "queue_manager.h"
#include "serial_stdio.h"

// Task 1: Button LED Task (10ms recurrence)
void ButtonLedTask(void *pvParameters) {
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = pdMS_TO_TICKS(10); // 10ms period
  
  // Initialize the xLastWakeTime variable with the current time
  xLastWakeTime = xTaskGetTickCount();
  
  while (1) {
    // Wait for the next cycle (ensures 10ms recurrence)
    vTaskDelayUntil(&xLastWakeTime, xPeriod);
    
    // Check if button is pressed
    if (isButtonPressed()) {
      // Button is pressed, turn on LED for 1 second
      turnOnLED(led1Pin);
      printf("Button pressed: LED ON for 1 second\n");
      
      // Give semaphore to signal Task 2
      giveButtonSemaphore();
      
      // Keep LED on for 1 second
      vTaskDelay(pdMS_TO_TICKS(1000));
      turnOffLED(led1Pin);
      
      // Wait for button release
      waitForButtonRelease();
    }
  }
}