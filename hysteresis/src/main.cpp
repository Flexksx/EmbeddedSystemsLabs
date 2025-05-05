#include <stdlib.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "TemperatureReader.h"
#include "Relay.h"
#include "SerialIo.h"

#define RELAY_PIN 10
#define TEMP_SENSOR_PIN A0

volatile double setPoint = 50.0;
volatile float hysteresis = 10.0;
volatile float currentTemp = 0.0;

TemperatureReader tempReader(TEMP_SENSOR_PIN);
Relay relay(RELAY_PIN);

TaskHandle_t tempSensorTaskHandle = NULL;
TaskHandle_t controlTaskHandle = NULL;
TaskHandle_t displayTaskHandle = NULL;
TaskHandle_t commandTaskHandle = NULL;

void tempSensorTask(void *pvParameters);
void controlTask(void *pvParameters);
void displayTask(void *pvParameters);
void commandTask(void *pvParameters);

int serial_putchar(char c, FILE *f)
{
  Serial.write(c);
  return 0;
}

int serial_getchar(FILE *f)
{
  while (Serial.available() == 0)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
  }
  return Serial.read();
}

void initPrintf()
{
  static FILE serial_stream;
  fdev_setup_stream(&serial_stream, serial_putchar, serial_getchar, _FDEV_SETUP_WRITE);
  stdout = &serial_stream;
  stdin = &serial_stream;
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }
  initPrintf();
  printf("Initializing Temperature Control System...\r\n");

  relay.init();

  xTaskCreate(tempSensorTask, "TempSensor", 128, NULL, 3, &tempSensorTaskHandle);
  xTaskCreate(controlTask, "Control", 128, NULL, 3, &controlTaskHandle);
  xTaskCreate(displayTask, "Display", 192, NULL, 2, &displayTaskHandle);
  xTaskCreate(commandTask, "Command", 128, NULL, 1, &commandTaskHandle);
}

void loop()
{
  // All work happens in FreeRTOS tasks
}

void tempSensorTask(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(200);

  for (;;)
  {
    currentTemp = tempReader.get();
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void controlTask(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(250);

  for (;;)
  {
    float cp = currentTemp;
    double sp = setPoint;
    float hys = hysteresis;

    float lowThreshold = sp - hys;
    float highThreshold = sp + hys;

    if (cp < lowThreshold && !relay.isOn())
    {
      relay.on();
    }
    else if (cp > highThreshold && relay.isOn())
    {
      relay.off();
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void displayTask(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(1000);

  for (;;)
  {
    // Use Serial.print to format floats correctly
    Serial.print("Temp: ");
    Serial.print(currentTemp, 1);
    Serial.print(" C  Set: ");
    Serial.print(setPoint, 1);
    Serial.print(" C  Relay: ");
    Serial.println(relay.isOn() ? "ON" : "OFF");

    if (currentTemp < 0)
    {
      Serial.println("Warning: Below 0 C!");
    }

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void commandTask(void *pvParameters)
{
  for (;;)
  {
    if (Serial.available() > 0)
    {
      char c = Serial.read();
      switch (c)
      {
      case 'u':
      case 'U':
        setPoint += 1.0;
        Serial.print("SetPoint ↑ → ");
        Serial.print(setPoint, 1);
        Serial.println(" C");
        break;
      case 'd':
      case 'D':
        setPoint -= 1.0;
        Serial.print("SetPoint ↓ → ");
        Serial.print(setPoint, 1);
        Serial.println(" C");
        break;
      default:
        break;
      }
    }
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}
