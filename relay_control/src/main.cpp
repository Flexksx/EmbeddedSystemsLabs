// Sketch.ino

#include <Arduino.h>
#include "SerialIo.h"
#include "Relay.h"

const int RELAY_PIN = 2;
Relay relay(RELAY_PIN);

void setup()
{
    Serial.begin(9600);
    SerialIo::init();
}

void loop()
{
    printf("Enter your command: ");
    fflush(stdout);

    char *cmd = SerialIo::input();

    if (strcmp(cmd, "relay on") == 0)
    {
        relay.on();
    }
    else if (strcmp(cmd, "relay off") == 0)
    {
        relay.off();
    }
    else if (strcmp(cmd, "relay toggle") == 0)
    {
        if (relay.isOn())
        {
            relay.off();
        }
        else
        {
            relay.on();
        }
        printf("Relay toggled.\r\n");
        fflush(stdout);
    }
    else
    {
        printf("Unknown command: %s\r\n", cmd);
        fflush(stdout);
    }

    printf("Current relay state: %s\r\n\r\n", relay.isOn() ? "ON" : "OFF");
    fflush(stdout);
}
