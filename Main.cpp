#include <iostream>
#include <memory>

#include "AccessControlSystem.h"
#include "BaseResponderUnit.h"
#include "CampusEmergencyFacade.h"
#include "CancelAlertCommand.h"
#include "CommunicationService.h"
#include "EmergencyMediator.h"
#include "FacilitiesStaff.h"
#include "Incident.h"
#include "LegacySystemAdapter.h"
#include "LockdownZoneCommand.h"
#include "MedicalResponder.h"
#include "Old1998ServerAccessHardware.h"
#include "OperatorInvoker.h"
#include "SecurityTeam.h"
#include "SirensEnabledDecorator.h"
#include "TriggerAlertCommand.h"
#include "UnpoweredConstructionZoneDecorator.h"
#include "VictimInterface.h"

int main()
{
    // SCENARIO 1: SECURITY THREAT IN A CONSTRUCTION ZONE
    // Demonstrates: State, Facade, Command, Mediator,

    {
        std::cout << "SCENARIO 1: Security threat in Engineering construction zone\n";

        Incident incident1(101,"Engineering construction zone","Unauthorised person detected near a restricted building entrance");

        EmergencyMediator mediator1("security threat",incident1.getLocation());

        // Adapter chain: AccessControlSystem -> ModernLockInterface
        // -> LegacySystemAdapter -> Old1998ServerAccessHardware.
        std::unique_ptr<Old1998ServerAccessHardware> legacyHardware1(new Old1998ServerAccessHardware());

        std::unique_ptr<ModernLockInterface> lockAdapter1(new LegacySystemAdapter(std::move(legacyHardware1)));

        AccessControlSystem accessControl1(std::move(lockAdapter1));

        CommunicationService communication1;
        FacilitiesStaff facilities1;
        MedicalResponder medical1;
        VictimInterface victim1;

        // Decorator chain for the security responder.
        std::unique_ptr<EmergencyResponder> baseSecurityResponder(new BaseResponderUnit("Campus security unit", 2));

        std::unique_ptr<EmergencyResponder> constructionResponder(new UnpoweredConstructionZoneDecorator(std::move(baseSecurityResponder)));

        std::unique_ptr<EmergencyResponder> decoratedSecurityResponder(new SirensEnabledDecorator(std::move(constructionResponder)));

        SecurityTeam security1(std::move(decoratedSecurityResponder));

        // Register the collaborating response components with the Mediator.
        accessControl1.reg(&mediator1);
        communication1.reg(&mediator1);
        facilities1.reg(&mediator1);
        medical1.reg(&mediator1);
        security1.reg(&mediator1);
        victim1.reg(&mediator1);

        // Command objects and Invoker.
        TriggerAlertCommand triggerAlert1(&mediator1);
        LockdownZoneCommand lockdown1(&mediator1);
        CancelAlertCommand cancelAlert1(&mediator1);

        OperatorInvoker invoker1(&triggerAlert1, &lockdown1, &cancelAlert1);

        // Facade combines the incident, commands and mediator workflow.
        CampusEmergencyFacade facade1(incident1,invoker1,mediator1);

        facade1.showIncidentStatus();

        // Invalid operation: lockdown is not allowed while only Reported.
        std::cout << "\nAttempting lockdown before crisis activation...\n";
        facade1.lockdownZone();

        // Normal workflow: State transition + Command + Mediator.
        std::cout << "\n Activating the panic-alert workflow...\n";
        facade1.handlePanicAlert();

        // Lockdown is now valid. The command is executed through the Invoker.
        std::cout << "\n Locking down the affected zone...\n";
        facade1.lockdownZone();

        // Additional mediator coordination so all response services visibly
        // participate in the runtime demonstration.
        mediator1.issueEvacuation("Evacuate the Engineering construction zone via the east assembly point.");

        std::cout << "\n[DEMO] Resolving Scenario 1...\n";
        facade1.resolveEmergency();
        facade1.showIncidentStatus();
    }

    // SCENARIO 2: MEDICAL EMERGENCY AT THE SPORTS CENTRE
    // Uses different runtime data and demonstrates the same integrated
    // architecture with the alert routed to a medical responder.
    {
        std::cout << "SCENARIO 2: Medical emergency at Sports Centre\n";
    
        Incident incident2(202,"Sports Centre","Student collapsed during a training session");

        EmergencyMediator mediator2("medical emergency",incident2.getLocation());

        // A separate legacy-access chain for the second runtime context.
        std::unique_ptr<Old1998ServerAccessHardware> legacyHardware2(new Old1998ServerAccessHardware());

        std::unique_ptr<ModernLockInterface> lockAdapter2(new LegacySystemAdapter(std::move(legacyHardware2)));

        AccessControlSystem accessControl2(std::move(lockAdapter2));

        CommunicationService communication2;
        FacilitiesStaff facilities2;
        SecurityTeam security2;
        VictimInterface victim2;

        // Decorate the medical responder with emergency sirens.
        std::unique_ptr<EmergencyResponder> baseMedicalResponder(new BaseResponderUnit("Campus medical unit", 3));

        std::unique_ptr<EmergencyResponder> decoratedMedicalResponder(new SirensEnabledDecorator(std::move(baseMedicalResponder)));

        MedicalResponder medical2(std::move(decoratedMedicalResponder));

        accessControl2.reg(&mediator2);
        communication2.reg(&mediator2);
        facilities2.reg(&mediator2);
        medical2.reg(&mediator2);
        security2.reg(&mediator2);
        victim2.reg(&mediator2);

        TriggerAlertCommand triggerAlert2(&mediator2);
        LockdownZoneCommand lockdown2(&mediator2);
        CancelAlertCommand cancelAlert2(&mediator2);

        OperatorInvoker invoker2(&triggerAlert2,&lockdown2,&cancelAlert2);

        CampusEmergencyFacade facade2(incident2,invoker2,mediator2);

        facade2.showIncidentStatus();

        std::cout << "\n Activating the medical-emergency workflow...\n";
        facade2.handlePanicAlert();

        // Mediator coordinates information to the wider response group.
        mediator2.issueEvacuation("Keep the Sports Centre entrance clear for the medical response team.");

        std::cout << "\nResolving Scenario 2...\n";
        facade2.resolveEmergency();
        facade2.showIncidentStatus();
    }
    return 0;
}
