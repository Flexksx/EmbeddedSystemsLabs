#ifndef PASSWORD_CONTROLLER_H
#define PASSWORD_CONTROLLER_H

class PasswordService
{
private:
    char *passcode;

public:
    PasswordService();
    ~PasswordService();
    bool setPasscode(const char *newPasscode);
    void deletePasscode();
    bool hasPasscode() const;
    bool matchPasscode(const char *passcodeToMatch) const;
};

#endif
