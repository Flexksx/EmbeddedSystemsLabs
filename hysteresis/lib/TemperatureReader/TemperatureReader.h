#ifndef TEMPERATURE_READER_H
#define TEMPERATURE_READER_H
#include <Arduino.h>

class TemperatureReader
{
private:
    int pin;

public:
    TemperatureReader(int sensorPin);
    float get();
};

#endif