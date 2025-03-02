#ifndef PASSWORD_CONTROLLER_H
#define PASSWORD_CONTROLLER_H

class PasswordController
{
private:
    char *passcode;

public:
    PasswordController();
    ~PasswordController();
    bool setPasscode(const char *newPasscode);
    void deletePasscode();
    bool hasPasscode() const;
    bool matchPasscode(const char *passcodeToMatch) const;
};

#endif
