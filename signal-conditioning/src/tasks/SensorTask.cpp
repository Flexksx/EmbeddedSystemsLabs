#include "SensorTask.h"
#include "PhotoResistor.h"
#include "SaltPepperFilter.h"
#include "MovingAverageFilter.h"

SensorData_t gSensorData = {0.0f};
SemaphoreHandle_t xSensorDataMutex = NULL;

// Optionally track final filtered value in a float
float gFilteredLux = 0.0f;

void vSensorTask(void *pvParameters)
{
    SensorTaskParams_t *params = (SensorTaskParams_t *)pvParameters;
    PhotoResistor *photoRes = params->pResistor;
    SaltPepperFilter *spFilter = params->pSpFilter;
    MovingAverageFilter *maFilter = params->pMaFilter;

    // Create the mutex if it doesn't exist yet
    if (xSensorDataMutex == NULL)
    {
        xSensorDataMutex = xSemaphoreCreateMutex();
    }

    const TickType_t xDelay = pdMS_TO_TICKS(100);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (true)
    {

        uint16_t rawVal = photoRes->readRawValue();

        float spFiltered = spFilter->filter(rawVal);

        float voltage = photoRes->convertADCToVoltage((uint16_t)spFiltered);
        float luxVal = photoRes->convertVoltageToLux(voltage);

        float finalLux = maFilter->filter(luxVal);

        Serial.print("Raw = ");
        Serial.print(rawVal);
        Serial.print(", S&P Filter = ");
        Serial.print(spFiltered);
        Serial.print(", Voltage = ");
        Serial.print(voltage);
        Serial.print(", Lux = ");
        Serial.print(luxVal);
        Serial.print(", MA Filtered = ");
        Serial.println(finalLux);

        if (xSemaphoreTake(xSensorDataMutex, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            gSensorData.brightness = finalLux;
            gFilteredLux = finalLux;
            xSemaphoreGive(xSensorDataMutex);
        }

        vTaskDelayUntil(&xLastWakeTime, xDelay);
    }
}
