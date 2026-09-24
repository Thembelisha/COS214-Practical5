#ifndef ACCESSCONTROLSYSTEM_H
#define ACCESSCONTROLSYSTEM_H

#include "ModernLockInterface.h"
#include "ResponseComponent.h"

#include <memory>
#include <string>

class AccessControlSystem : public ResponseComponent
{
public:
    AccessControlSystem();
    explicit AccessControlSystem(std::unique_ptr<ModernLockInterface> lockController);

    bool lockDoor(int doorId);
    bool unlockDoor(int doorId);
    bool restrictArea(const std::string& areaCode);

    void receiveEmergencyMessage(std::string myId, std::string em) override;
    void sendResponse() override;

private:
    std::unique_ptr<ModernLockInterface> lockController;
};

#endif
