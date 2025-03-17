#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

// Semaphore for task synchronization
extern SemaphoreHandle_t buttonSemaphore;

// Queue for data transfer between tasks
extern QueueHandle_t dataQueue;
extern const int queueSize;

// Global variables
extern volatile int N;         // Counter variable for Task 2

// Function prototypes
bool initializeSemaphore();
bool initializeQueue();
bool sendDataToQueue(uint8_t data);
bool receiveDataFromQueue(uint8_t* data);
bool giveButtonSemaphore();
bool takeButtonSemaphore(TickType_t timeout);

#endif