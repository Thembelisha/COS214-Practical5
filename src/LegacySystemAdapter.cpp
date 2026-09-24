#include "LegacySystemAdapter.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

LegacySystemAdapter::LegacySystemAdapter()
    : legacyHardware(new Old1998ServerAccessHardware())
{
}

LegacySystemAdapter::LegacySystemAdapter(
    std::unique_ptr<Old1998ServerAccessHardware> legacyHardware)
    : legacyHardware(std::move(legacyHardware))
{
    if (!this->legacyHardware) {
        throw std::invalid_argument("LegacySystemAdapter requires legacy access hardware.");
    }
}

bool LegacySystemAdapter::lockDoor(int doorId)
{
    if (!validDoorId(doorId)) {
        std::cout << "[Adapter] Cannot lock invalid door ID " << doorId << "." << std::endl;
        return false;
    }

    const std::string rawCommand = doorCommand("LOCK", doorId);
    std::cout << "[Adapter] Translating lockDoor(" << doorId
              << ") to " << rawCommand << "." << std::endl;
    return legacyHardware->transmitRawString(rawCommand);
}

bool LegacySystemAdapter::unlockDoor(int doorId)
{
    if (!validDoorId(doorId)) {
        std::cout << "[Adapter] Cannot unlock invalid door ID " << doorId << "." << std::endl;
        return false;
    }

    const std::string rawCommand = doorCommand("UNLOCK", doorId);
    std::cout << "[Adapter] Translating unlockDoor(" << doorId
              << ") to " << rawCommand << "." << std::endl;
    return legacyHardware->transmitRawString(rawCommand);
}

bool LegacySystemAdapter::restrictArea(const std::string& areaCode)
{
    const std::string normalisedAreaCode = normaliseAreaCode(areaCode);
    if (normalisedAreaCode.empty()) {
        std::cout << "[Adapter] Cannot restrict invalid area code: "
                  << areaCode << "." << std::endl;
        return false;
    }

    const std::string rawCommand = "CMD_RESTRICT_" + normalisedAreaCode;
    std::cout << "[Adapter] Translating restrictArea(\"" << areaCode
              << "\") to " << rawCommand << "." << std::endl;
    return legacyHardware->transmitRawString(rawCommand);
}

bool LegacySystemAdapter::validDoorId(int doorId) const
{
    return doorId > 0 && doorId <= 0xFFFF;
}

std::string LegacySystemAdapter::doorCommand(
    const std::string& operation, int doorId) const
{
    std::ostringstream command;
    command << "CMD_" << operation << "_0x"
            << std::uppercase << std::hex << doorId;
    return command.str();
}

std::string LegacySystemAdapter::normaliseAreaCode(
    const std::string& areaCode) const
{
    if (areaCode.empty()) {
        return "";
    }

    std::string normalised = areaCode;
    for (std::string::iterator it = normalised.begin(); it != normalised.end(); ++it) {
        const unsigned char character = static_cast<unsigned char>(*it);
        if (!std::isalnum(character) && *it != '_' && *it != '-') {
            return "";
        }
        *it = static_cast<char>(std::toupper(character));
    }
    return normalised;
}
