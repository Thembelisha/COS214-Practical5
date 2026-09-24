#include "AccessControlSystem.h"

#include "CampusMediator.h"
#include "LegacySystemAdapter.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

AccessControlSystem::AccessControlSystem()
    : AccessControlSystem(std::unique_ptr<ModernLockInterface>(
          new LegacySystemAdapter()))
{
}

AccessControlSystem::AccessControlSystem(
    std::unique_ptr<ModernLockInterface> lockController)
    : ResponseComponent(), lockController(std::move(lockController))
{
    if (!this->lockController) {
        throw std::invalid_argument(
            "AccessControlSystem requires a modern lock controller.");
    }

    myId = "access-control-1";
    setCategory("access");
}

bool AccessControlSystem::lockDoor(int doorId)
{
    return lockController->lockDoor(doorId);
}

bool AccessControlSystem::unlockDoor(int doorId)
{
    return lockController->unlockDoor(doorId);
}

bool AccessControlSystem::restrictArea(const std::string& areaCode)
{
    return lockController->restrictArea(areaCode);
}

void AccessControlSystem::receiveEmergencyMessage(
    std::string myId, std::string em)
{
    const int emergencyDoorId = 79;
    const std::string emergencyArea = "EMERGENCY_PERIMETER";

    std::cout << myId << " received emergency: " << em << std::endl;
    std::cout << "AccessControlSystem: restricting the incident perimeter "
              << "and locking the nearest legacy-controlled door." << std::endl;

    const bool areaRestricted = restrictArea(emergencyArea);
    const bool doorLocked = lockDoor(emergencyDoorId);

    if (areaRestricted && doorLocked) {
        std::cout << "AccessControlSystem: Legacy access operations acknowledged."
                  << std::endl;
    } else {
        std::cout << "AccessControlSystem: One or more access operations failed."
                  << std::endl;
    }
}

void AccessControlSystem::sendResponse()
{
    std::string toId;
    std::string msg;

    std::cout << "AccessControl " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "AccessControl " << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (emergency != nullptr) {
        emergency->communicate(toId, myId + ": " + msg);
    }
}
