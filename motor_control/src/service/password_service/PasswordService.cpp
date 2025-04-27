#include <service/password_service/PasswordService.h>
#include <Arduino.h>
#include <string.h>
#include <ctype.h>

PasswordService::PasswordService()
    : passcode(nullptr)
{
}

PasswordService::~PasswordService()
{
    deletePasscode();
}

bool PasswordService::setPasscode(const char *newPasscode)
{
    if (newPasscode == NULL)
    {
        Serial.println("Error: Passcode cannot be null.");
        return false;
    }

    size_t len = strlen(newPasscode);
    if (len != 4)
    {
        Serial.println("Error: Passcode must be exactly 4 characters long.");
        return false;
    }

    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(newPasscode[i]))
        {
            Serial.println("Error: Passcode must contain only numeric digits.");
            return false;
        }
    }

    if (passcode != NULL)
    {
        delete[] passcode;
    }

    passcode = new char[len + 1];
    strncpy(passcode, newPasscode, len);
    passcode[len] = '\0';

    return true;
}

void PasswordService::deletePasscode()
{
    if (passcode != NULL)
    {
        delete[] passcode;
        passcode = NULL;
    }
}

bool PasswordService::hasPasscode() const
{
    return (passcode != NULL) && (strlen(passcode) == 4);
}

bool PasswordService::matchPasscode(const char *passcodeToMatch) const
{
    if (passcode == NULL || passcodeToMatch == NULL)
    {
        return false;
    }
    return strcmp(passcode, passcodeToMatch) == 0;
}
