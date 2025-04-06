#include "SensorTask.h"
#include "PhotoResistor.h"
#include "SaltPepperFilter.h"
#include "MovingAverageFilter.h"

SensorData_t gSensorData = {0.0f};
SemaphoreHandle_t xSensorDataMutex = NULL;
float gFilteredLux = 0.0f;

void vSensorTask(void *pvParameters)
{
    SensorTaskParams_t *params = (SensorTaskParams_t *)pvParameters;
    PhotoResistor *photoRes = params->pResistor;
    SaltPepperFilter *spFilter = params->pSpFilter;
    MovingAverageFilter *maFilter = params->pMaFilter;

    if (xSensorDataMutex == NULL)
    {
        xSensorDataMutex = xSemaphoreCreateMutex();
    }

    const TickType_t xDelay = pdMS_TO_TICKS(500);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        uint16_t rawVal = photoRes->readRawValue();

        float spFiltered = spFilter->filter(rawVal);
        float voltage = photoRes->convertADCToVoltage((uint16_t)spFiltered);
        float luxVal = photoRes->convertVoltageToLux(voltage);
        float finalLux = maFilter->filter(luxVal);

        if (xSemaphoreTake(xSensorDataMutex, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            gSensorData.brightness = finalLux;
            xSemaphoreGive(xSensorDataMutex);
        }

        vTaskDelayUntil(&xLastWakeTime, xDelay);
    }
}
