#include "MovingAverageFilter.h"

MovingAverageFilter::MovingAverageFilter(uint8_t windowSize)
{
    this->windowSize = windowSize;
    buffer = new float[windowSize];
    index = 0;
}

MovingAverageFilter::~MovingAverageFilter()
{
    delete[] buffer;
}

void MovingAverageFilter::begin()
{
    for (uint8_t i = 0; i < windowSize; i++)
    {
        buffer[i] = 0.0f;
    }
}

float MovingAverageFilter::filter(float newSample)
{
    buffer[index] = newSample;
    index = (index + 1) % windowSize;

    float sum = 0.0f;
    for (uint8_t i = 0; i < windowSize; i++)
    {
        sum += buffer[i];
    }

    return sum / windowSize;
}
