#ifndef SALTPEPPERFILTER_H
#define SALTPEPPERFILTER_H

#include <Arduino.h>

class SaltPepperFilter
{
public:
    SaltPepperFilter(uint8_t windowSize);
    ~SaltPepperFilter();

    void begin();
    float filter(uint16_t newSample);

private:
    uint8_t windowSize;
    uint16_t *buffer;
    uint8_t bufferIndex;
};

#endif // SALTPEPPERFILTER_H
