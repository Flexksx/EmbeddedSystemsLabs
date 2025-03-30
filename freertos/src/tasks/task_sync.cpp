#include "task_sync.h"
#include "led_control.h"
#include "queue_semaphore_service.h"
#include "serial_stdio.h"

void SyncTask(void *pvParameters)
{
  const TickType_t xDelay = pdMS_TO_TICKS(50);
  uint8_t data;

  while (1)
  {
    if (takeButtonSemaphore(portMAX_DELAY))
    {
      N++;
      printf("Task 2: N incremented to %d\n", N);

      printf("Task 2: Sending %d bytes to queue: ", N);
      for (int i = 1; i <= N; i++)
      {
        data = i;
        printf("%d ", data);
        sendDataToQueue(data);
        vTaskDelay(xDelay);
      }

      data = 0;
      sendDataToQueue(data);
      printf("0 (end marker)\n");

      printf("Task 2: Blinking LED %d times\n", N);
      blinkLED(led2Pin, N, 300, 500);
    }
  }
}