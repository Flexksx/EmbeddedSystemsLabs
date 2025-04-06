#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/**
 * Holds the final filtered brightness.
 */
typedef struct
{
    float brightness;
} SensorData_t;

/**
 * This struct is used to pass references into the Sensor Task
 * (photoresistor + filters).
 */
typedef struct
{
    class PhotoResistor *pResistor; // forward-declare if needed
    class SaltPepperFilter *pSpFilter;
    class MovingAverageFilter *pMaFilter;
} SensorTaskParams_t;

// Global data & mutex
extern SensorData_t gSensorData;
extern SemaphoreHandle_t xSensorDataMutex;

// The FreeRTOS task
void vSensorTask(void *pvParameters);

#endif
