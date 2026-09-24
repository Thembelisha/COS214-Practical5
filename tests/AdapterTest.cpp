#include "AccessControlSystem.h"
#include "LegacySystemAdapter.h"
#include "ModernLockInterface.h"
#include "Old1998ServerAccessHardware.h"

#include <cassert>
#include <memory>
#include <string>
#include <utility>
#include <vector>

int main()
{
    Old1998ServerAccessHardware* observedHardware =
        new Old1998ServerAccessHardware();
    std::unique_ptr<Old1998ServerAccessHardware> ownedHardware(observedHardware);
    std::unique_ptr<ModernLockInterface> adapter(
        new LegacySystemAdapter(std::move(ownedHardware)));

    AccessControlSystem accessControl(std::move(adapter));

    assert(accessControl.lockDoor(79));
    assert(accessControl.unlockDoor(79));
    assert(accessControl.restrictArea("construction_zone"));
    assert(!accessControl.lockDoor(0));
    assert(!accessControl.restrictArea("invalid area"));

    const std::vector<std::string>& commands = observedHardware->getCommandLog();
    assert(commands.size() == 3);
    assert(commands[0] == "CMD_LOCK_0x4F");
    assert(commands[1] == "CMD_UNLOCK_0x4F");
    assert(commands[2] == "CMD_RESTRICT_CONSTRUCTION_ZONE");

    accessControl.receiveEmergencyMessage(
        "access-control-1", "Security incident at Engineering Block");

    assert(commands.size() == 5);
    assert(commands[3] == "CMD_RESTRICT_EMERGENCY_PERIMETER");
    assert(commands[4] == "CMD_LOCK_0x4F");
    return 0;
}
