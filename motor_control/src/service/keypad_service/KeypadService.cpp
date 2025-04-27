#include "KeypadService.h"

KeypadService *KeypadService::instance = nullptr;

KeypadService::KeypadService()
    : keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS)
{

    instance = this;
}

void KeypadService::setupStdioKeypad()
{
    FILE *keypadStream = fdevopen(nullptr, keypadRead);
    stdin = keypadStream;
}

int KeypadService::keypadRead(FILE *stream)
{
    static char lastKey = 0;

    while (true)
    {

        char currentKey = instance->keypad.getKey();

        if (!currentKey)
        {
            lastKey = 0;
            continue;
        }
        if (currentKey != lastKey)
        {
            lastKey = currentKey;
            Serial.println("Read from keypad: ");
            Serial.print(currentKey);

            return currentKey;
        }
    }
}
