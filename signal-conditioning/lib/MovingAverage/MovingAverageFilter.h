#ifndef MOVINGAVERAGEFILTER_H
#define MOVINGAVERAGEFILTER_H

#include <Arduino.h>

class MovingAverageFilter
{
public:
    MovingAverageFilter(uint8_t windowSize);
    ~MovingAverageFilter();

    void begin();
    float filter(float newSample);

private:
    float *buffer;
    uint8_t windowSize;
    uint8_t index;
};

#endif // MOVINGAVERAGEFILTER_H
