#ifndef LEGACYSYSTEMADAPTER_H
#define LEGACYSYSTEMADAPTER_H

#include "ModernLockInterface.h"
#include "Old1998ServerAccessHardware.h"

#include <memory>
#include <string>

class LegacySystemAdapter : public ModernLockInterface
{
public:
    LegacySystemAdapter();
    explicit LegacySystemAdapter(
        std::unique_ptr<Old1998ServerAccessHardware> legacyHardware);

    bool lockDoor(int doorId) override;
    bool unlockDoor(int doorId) override;
    bool restrictArea(const std::string& areaCode) override;

private:
    bool validDoorId(int doorId) const;
    std::string doorCommand(const std::string& operation, int doorId) const;
    std::string normaliseAreaCode(const std::string& areaCode) const;

    std::unique_ptr<Old1998ServerAccessHardware> legacyHardware;
};

#endif
