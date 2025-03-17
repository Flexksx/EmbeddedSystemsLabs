#include "task_sync.h"
#include "led_control.h"
#include "queue_manager.h"
#include "serial_stdio.h"

// Task 2: Synchronous Task (waits for semaphore)
void SyncTask(void *pvParameters) {
  const TickType_t xDelay = pdMS_TO_TICKS(50); // 50ms interval
  uint8_t data;
  
  while (1) {
    // Wait for the semaphore from Task 1
    if (takeButtonSemaphore(portMAX_DELAY)) {
      // Increment N
      N++;
      printf("Task 2: N incremented to %d\n", N);
      
      // Send N bytes (1,2,3,...N) to the queue
      printf("Task 2: Sending %d bytes to queue: ", N);
      for (int i = 1; i <= N; i++) {
        data = i;
        printf("%d ", data);
        sendDataToQueue(data);
        vTaskDelay(xDelay); // 50ms interval between bytes
      }
      
      // Send delimiter (0) to indicate end of sequence
      data = 0;
      sendDataToQueue(data);
      printf("0 (end marker)\n");
      
      // Blink LED N times with ON=300ms, OFF=500ms
      printf("Task 2: Blinking LED %d times\n", N);
      blinkLED(led2Pin, N, 300, 500);
    }
  }
}