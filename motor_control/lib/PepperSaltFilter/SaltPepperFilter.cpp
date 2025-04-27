#include "SaltPepperFilter.h"
#include <string.h>

SaltPepperFilter::SaltPepperFilter(uint8_t windowSize)
{
    this->windowSize = windowSize;
    buffer = new uint16_t[windowSize];
    bufferIndex = 0;
}

SaltPepperFilter::~SaltPepperFilter()
{
    delete[] buffer;
}

void SaltPepperFilter::begin()
{
    for (uint8_t i = 0; i < windowSize; i++)
    {
        buffer[i] = 0;
    }
}

float SaltPepperFilter::filter(uint16_t newSample)
{
    buffer[bufferIndex] = newSample;
    bufferIndex = (bufferIndex + 1) % windowSize;

    uint16_t sorted[windowSize];
    memcpy(sorted, buffer, sizeof(uint16_t) * windowSize);

    for (uint8_t i = 0; i < windowSize - 1; i++)
    {
        for (uint8_t j = 0; j < windowSize - i - 1; j++)
        {
            if (sorted[j] > sorted[j + 1])
            {
                uint16_t tmp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = tmp;
            }
        }
    }

    return sorted[windowSize / 2]; // median
}
