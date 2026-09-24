#ifndef MODERNLOCKINTERFACE_H
#define MODERNLOCKINTERFACE_H

#include <string>

class ModernLockInterface
{
public:
    virtual ~ModernLockInterface() {}

    virtual bool lockDoor(int doorId) = 0;
    virtual bool unlockDoor(int doorId) = 0;
    virtual bool restrictArea(const std::string& areaCode) = 0;
};

#endif
