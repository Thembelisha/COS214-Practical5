#include "AccessControlSystem.h"
#include "BaseResponderUnit.h"
#include "CampusEmergencyFacade.h"
#include "CampusMediator.h"
#include "CancelAlertCommand.h"
#include "CommunicationService.h"
#include "EmergencyCommand.h"
#include "EmergencyMediator.h"
#include "EmergencyResponder.h"
#include "EvacuationInstructionDecorator.h"
#include "Incident.h"
#include "LegacySystemAdapter.h"
#include "LockdownZoneCommand.h"
#include "MedicalResponder.h"
#include "ModernLockInterface.h"
#include "Old1998ServerAccessHardware.h"
#include "OperatorInvoker.h"
#include "ResponseComponent.h"
#include "SecurityTeam.h"
#include "SirensEnabledDecorator.h"
#include "TriggerAlertCommand.h"
#include "UnpoweredConstructionZoneDecorator.h"
#include "VictimInterface.h"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class RecordingComponent : public ResponseComponent {
public:
    RecordingComponent(const std::string& id, const std::string& category)
        : receivedMessages(0) {
        setId(id);
        setCategory(category);
    }

    void receiveEmergencyMessage(std::string, std::string message) override {
        ++receivedMessages;
        lastMessage = message;
    }

    void sendResponse() override {
    }

    int receivedMessages;
    std::string lastMessage;
};

static void runAdapterTest() {
    Old1998ServerAccessHardware* observedHardware = new Old1998ServerAccessHardware();
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
}

static void runCommandDecoratorTest() {
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
}

static void runDecoratorTest() {
    std::unique_ptr<EmergencyResponder> basicSecurityUnit(
        new BaseResponderUnit("Test security unit", 2));
    std::unique_ptr<EmergencyResponder> constructionSecurityUnit(
        new UnpoweredConstructionZoneDecorator(std::move(basicSecurityUnit)));
    std::unique_ptr<EmergencyResponder> fullyEquippedSecurityUnit(
        new SirensEnabledDecorator(std::move(constructionSecurityUnit)));

    assert(fullyEquippedSecurityUnit->getClearanceLevel() == 4);
    assert(fullyEquippedSecurityUnit->getCapabilities().find("thermal tracking") != std::string::npos);
    assert(fullyEquippedSecurityUnit->getCapabilities().find("emergency sirens") != std::string::npos);

    SecurityTeam securityTeam(std::move(fullyEquippedSecurityUnit));
    securityTeam.receiveEmergencyMessage(
        "security-team-1", "Engineering construction zone");

    std::unique_ptr<EmergencyResponder> basicMedicalUnit(
        new BaseResponderUnit("Test medical unit", 3));
    std::unique_ptr<EmergencyResponder> priorityMedicalUnit(
        new SirensEnabledDecorator(std::move(basicMedicalUnit)));
    MedicalResponder medicalResponder(std::move(priorityMedicalUnit));
    medicalResponder.receiveEmergencyMessage(
        "medical-responder-1", "Engineering construction zone");

    bool rejectedNullResponder = false;
    try {
        std::unique_ptr<EmergencyResponder> missingResponder;
        SirensEnabledDecorator invalidDecorator(std::move(missingResponder));
    } catch (const std::invalid_argument&) {
        rejectedNullResponder = true;
    }

    assert(rejectedNullResponder);
}

static void runIntegratedApplicationWorkflow() {
    Incident incident(42, "Engineering Block", "Fire in the server room");
    EmergencyMediator mediator("medical", "Engineering Block");

    AccessControlSystem accessControl;
    CommunicationService communication;
    MedicalResponder medical;
    SecurityTeam security;
    VictimInterface victim;

    accessControl.reg(&mediator);
    communication.reg(&mediator);
    medical.reg(&mediator);
    security.reg(&mediator);
    victim.reg(&mediator);

    TriggerAlertCommand alertCommand(&mediator);
    LockdownZoneCommand lockdownCommand(&mediator);
    CancelAlertCommand cancelCommand(&mediator);
    OperatorInvoker invoker(&alertCommand, &lockdownCommand, &cancelCommand);
    CampusEmergencyFacade facade(incident, invoker, mediator);

    facade.handlePanicAlert();
    assert(incident.getStateName() == "ActiveCrisis");
    assert(incident.canDeployResponders());
    assert(incident.canLockdownZone());

    std::unique_ptr<EmergencyCommand> decoratedAlert(
        new TriggerAlertCommand(&mediator));
    EvacuationInstructionDecorator evacuationDecorator(
        std::move(decoratedAlert),
        mediator,
        "Use the east exit and report to the assembly point");
    evacuationDecorator.execute();

    facade.lockdownZone();
    facade.resolveEmergency();
    assert(incident.getStateName() == "Resolved");

    facade.handlePanicAlert();
    assert(incident.getStateName() == "Resolved");
}

int main() {
    runAdapterTest();
    runCommandDecoratorTest();
    runDecoratorTest();
    runIntegratedApplicationWorkflow();
    return 0;
}
