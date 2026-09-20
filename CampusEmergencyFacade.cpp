#include "CampusEmergencyFacade.h"

#include "Incident.h"
#include "OperatorInvoker.h"
#include "EmergencyMediator.h"
#include "TriggerAlertCommand.h"

#include <iostream>
#include <memory>

CampusEmergencyFacade::CampusEmergencyFacade(Incident& incident,OperatorInvoker& invoker,EmergencyMediator& mediator)
: incident(incident),invoker(invoker),mediator(mediator)
{

}

void CampusEmergencyFacade::handlePanicAlert()
{
    std::cout << " CAMPUSGUARD - PANIC ALERT RECEIVED\n";
    // STEP 1:
    // Check current lifecycle state.
    incident.validateStatus();

    // Prevent invalid repeated activation.
    if (incident.getStateName() == "Resolved")
    {
        cout<< "[FACADE] Cannot activate a resolved incident."<< std::endl;
        return;
    }

    // STEP 2:
    // State Pattern
    incident.activateCrisis();

    incident.evaluatePermissions();

    // STEP 3:
    // Command Pattern
    std::unique_ptr<EmergencyCommand> command(new TriggerAlertCommand(mediator, incident)
    );

    // STEP 4:
    // Invoker executes the command.
    invoker.executeCommand(std::move(command));

    std::cout << "[FACADE] Panic-alert workflow completed."<< std::endl;
}

void CampusEmergencyFacade::resolveEmergency()
{
    std::cout << " CAMPUSGUARD - RESOLVING INCIDENT\n";
    incident.resolveIncident();

    incident.evaluatePermissions();

    std::cout << "[FACADE] Emergency stand-down completed."<< std::endl;
}

void CampusEmergencyFacade::showIncidentStatus() const
{
    std::cout << "\nIncident #" << incident.getId()<< "\nLocation: " << incident.getLocation()<< "\nDescription: " << incident.getDescription()<< "\nStatus: " << incident.getStateName()<< "\n";
}