#include "CampusMediator.h"
#include "EmergencyCommand.h"
#include "EmergencyMediator.h"
#include "EvacuationInstructionDecorator.h"
#include "LockdownZoneCommand.h"
#include "ResponseComponent.h"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

class RecordingComponent : public ResponseComponent
{
public:
    RecordingComponent(const std::string& id, const std::string& category)
        : receivedMessages(0)
    {
        setId(id);
        setCategory(category);
    }

    void receiveEmergencyMessage(std::string, std::string message) override
    {
        ++receivedMessages;
        lastMessage = message;
    }

    void sendResponse() override
    {
    }

    int receivedMessages;
    std::string lastMessage;
};

int main()
{
    EmergencyMediator mediator("security threat", "Engineering Block");
    RecordingComponent communication("communication-test", "communication");
    RecordingComponent security("security-test", "security");
    RecordingComponent medical("medical-test", "medical");
    RecordingComponent facilities("facilities-test", "facilities");
    RecordingComponent accessControl("access-test", "access");

    communication.reg(&mediator);
    security.reg(&mediator);
    medical.reg(&mediator);
    facilities.reg(&mediator);
    accessControl.reg(&mediator);

    std::unique_ptr<EmergencyCommand> lockdownCommand(
        new LockdownZoneCommand(&mediator));
    EvacuationInstructionDecorator evacuationLockdown(
        std::move(lockdownCommand),
        mediator,
        "Use the eastern assembly point and assist injured students");

    evacuationLockdown.execute();

    assert(communication.receivedMessages == 1);
    assert(security.receivedMessages == 1);
    assert(medical.receivedMessages == 1);
    assert(facilities.receivedMessages == 1);
    assert(accessControl.receivedMessages == 0);
    assert(security.lastMessage.find("eastern assembly point") != std::string::npos);

    bool rejectedEmptyInstructions = false;
    try {
        std::unique_ptr<EmergencyCommand> secondLockdown(
            new LockdownZoneCommand(&mediator));
        EvacuationInstructionDecorator invalidDecorator(
            std::move(secondLockdown), mediator, "");
    } catch (const std::invalid_argument&) {
        rejectedEmptyInstructions = true;
    }

    assert(rejectedEmptyInstructions);
    return 0;
}
