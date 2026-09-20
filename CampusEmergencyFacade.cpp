#include "CampusEmergencyFacade.h"

#include "Incident.h"
#include "OperatorInvoker.h"
#include "EmergencyMediator.h"

#include <iostream>

CampusEmergencyFacade::CampusEmergencyFacade(Incident& incident,OperatorInvoker& invoker,EmergencyMediator& mediator)
: incident(incident),invoker(invoker),mediator(mediator)
{

}

void CampusEmergencyFacade::handlePanicAlert()
{
    std::cout << "CAMPUSGUARD - PANIC ALERT RECEIVED\n";

    incident.validateStatus();

    if (incident.getStateName() == "Resolved")
    {
        std::cout<< "[FACADE] Cannot activate a resolved incident."<< std::endl;
        return;
    }

    incident.activateCrisis();

    incident.evaluatePermissions();

    // Command Pattern through Member 2's Invoker
    invoker.alert();

    std::cout<< "[FACADE] Panic-alert workflow completed."<< std::endl;
}
void CampusEmergencyFacade::resolveEmergency()
{
    std::cout << " CAMPUSGUARD - RESOLVING INCIDENT\n";
    incident.resolveIncident();
    invoker.noAlert();
    incident.evaluatePermissions();

    std::cout << "[FACADE] Emergency stand-down completed."<< std::endl;
}

void CampusEmergencyFacade::showIncidentStatus() const
{
    std::cout << "\nIncident #" << incident.getId()<< "\nLocation: " << incident.getLocation()<< "\nDescription: " << incident.getDescription()<< "\nStatus: " << incident.getStateName()<< "\n";
}
void CampusEmergencyFacade::lockdownZone()
{
    if (!incident.canLockdownZone())
    {
        std::cout<< "[FACADE] Lockdown denied in state: "<< incident.getStateName()<< std::endl;
        return;
    }

    invoker.lockDown();
}