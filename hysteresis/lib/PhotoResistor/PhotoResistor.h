// PhotoResistor.h
// A simple library to read values from a photoresistor (LDR) using an Arduino
// This library provides methods to read the raw ADC value, convert it to voltage,
// and convert that voltage to lux (light intensity).

#ifndef PHOTORISTOR_H
#define PHOTORISTOR_H

#include <Arduino.h>

class PhotoResistor
{
private:
    uint8_t pin;         // Analog pin the photoresistor is connected to
    float voltRef;       // Reference voltage (typically 5.0V or 3.3V)
    float adcResolution; // ADC resolution (typically 1023 for 10-bit ADC)

    float minVolt;
    float maxVolt;
    float minLux;
    float maxLux;

public:
    PhotoResistor(uint8_t pin, float voltRef = 5.0, float adcResolution = 1023.0,
                  float minVolt = 0.0, float maxVolt = 5.0,
                  float minLux = 0, float maxLux = 1000);

    // Methods
    void begin();
    uint16_t readRawValue();
    float convertADCToVoltage(uint16_t adcValue);
    float convertVoltageToLux(float voltage);
    float readLux();
};

#endif