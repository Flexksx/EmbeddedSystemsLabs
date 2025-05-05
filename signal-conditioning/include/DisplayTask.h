#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

class LCD;

void vDisplayTask(void *pvParameters);

#endif // DISPLAY_TASK_H
