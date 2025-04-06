#include <Arduino.h>
#include "SensorTask.h"
#include "PhotoResistor.h"
#include "SaltPepperFilter.h"
#include "MovingAverageFilter.h"
#include <Arduino_FreeRTOS.h>

PhotoResistor photo(A0, 5.0f, 1023.0f, 0.0f, 5.0f, 0.0f, 1000.0f);
SaltPepperFilter spFilter(5);
MovingAverageFilter maFilter(5);

static SensorTaskParams_t sensorParams = {
    &photo,
    &spFilter,
    &maFilter};

extern void vDisplayTask(void *);

void setup()
{
  Serial.begin(115200);

  photo.begin();
  spFilter.begin();
  maFilter.begin();

  xTaskCreate(
      vSensorTask,
      "Sensor",
      256,
      &sensorParams,
      2,
      NULL);

  xTaskCreate(
      vDisplayTask,
      "Display",
      256,
      NULL,
      1,
      NULL);

  vTaskStartScheduler();
}

void loop()
{
  // FreeRTOS takes over
}
