#include "task_async.h"
#include "queue_semaphore_service.h"
#include "serial_stdio.h"

// Task 3: Asynchronous Task (reads queue every 200ms)
void AsyncTask(void *pvParameters)
{
  const TickType_t xDelay = pdMS_TO_TICKS(200); // 200ms interval
  uint8_t receivedData;

  while (1)
  {
    // Wait for the next cycle (200ms)
    vTaskDelay(xDelay);

    printf("Task 3: Reading queue - ");

    while (receiveDataFromQueue(&receivedData))
    {
      if (receivedData == 0)
      {
        printf("\nTask 3: End of sequence detected\n");
      }
      else
      {
        // Print the received byte
        printf("%d ", receivedData);
      }
    }

    printf("\n");
  }
}