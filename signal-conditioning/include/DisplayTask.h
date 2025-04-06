#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

// We only need to forward-declare the LCD if you want to pass an LCD pointer
// via parameters. Otherwise we can handle it globally.
class LCD;

/**
 * FreeRTOS task function that periodically:
 * 1) Acquires the mutex
 * 2) Reads the global brightness from gSensorData
 * 3) Displays on the LCD or via printf()
 */
void vDisplayTask(void *pvParameters);

#endif // DISPLAY_TASK_H
