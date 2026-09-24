#include "Old1998ServerAccessHardware.h"

#include <iostream>

bool Old1998ServerAccessHardware::transmitRawString(const std::string& rawCommand)
{
    const bool recognisedCommand =
        rawCommand.find("CMD_LOCK_0x") == 0
        || rawCommand.find("CMD_UNLOCK_0x") == 0
        || rawCommand.find("CMD_RESTRICT_") == 0;

    if (!recognisedCommand) {
        std::cout << "[Legacy Access] Rejected malformed command: "
                  << rawCommand << std::endl;
        return false;
    }

    commandLog.push_back(rawCommand);
    std::cout << "[Legacy Access] Transmitted raw command: "
              << rawCommand << std::endl;
    return true;
}

const std::vector<std::string>& Old1998ServerAccessHardware::getCommandLog() const
{
    return commandLog;
}
