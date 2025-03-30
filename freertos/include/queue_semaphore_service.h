#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

extern SemaphoreHandle_t buttonSemaphore;

extern QueueHandle_t dataQueue;
extern const int queueSize;

extern volatile int N;

bool initializeSemaphore();
bool initializeQueue();
bool sendDataToQueue(uint8_t data);
bool receiveDataFromQueue(uint8_t *data);
bool giveButtonSemaphore();
bool takeButtonSemaphore(TickType_t timeout);

#endif