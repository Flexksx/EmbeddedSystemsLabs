#ifndef RELAY_H
#define RELAY_H
#include <Arduino.h>

class Relay
{
private:
    int pin;
    bool state;

public:
    Relay(int relayPin);
    void init();
    void on();
    void off();
    bool isOn();
};

#endif // RELAY_H