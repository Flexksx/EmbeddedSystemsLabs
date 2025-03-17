#include "queue_manager.h"

// Semaphore for task synchronization
SemaphoreHandle_t buttonSemaphore = NULL;

// Queue for data transfer between tasks
QueueHandle_t dataQueue = NULL;
const int queueSize = 32;   // Max buffer size

// Global variables
volatile int N = 0;         // Counter variable for Task 2

bool initializeSemaphore() {
  buttonSemaphore = xSemaphoreCreateBinary();
  return buttonSemaphore != NULL;
}

bool initializeQueue() {
  dataQueue = xQueueCreate(queueSize, sizeof(uint8_t));
  return dataQueue != NULL;
}

bool sendDataToQueue(uint8_t data) {
  return xQueueSendToBack(dataQueue, &data, portMAX_DELAY) == pdTRUE;
}

bool receiveDataFromQueue(uint8_t* data) {
  return xQueueReceive(dataQueue, data, 0) == pdTRUE;
}

bool giveButtonSemaphore() {
  return xSemaphoreGive(buttonSemaphore) == pdTRUE;
}

bool takeButtonSemaphore(TickType_t timeout) {
  return xSemaphoreTake(buttonSemaphore, timeout) == pdTRUE;
}