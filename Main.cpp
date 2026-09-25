#include <iostream>
#include <string>

#include "AccessControlSystem.h"
#include "CommunicationService.h"
#include "EmergencyMediator.h"
#include "MedicalResponder.h"
#include "SecurityTeam.h"
#include "TriggerAlertCommand.h"
#include "VictimInterface.h"

int main() {
    
    std::cout << "Choose the type of incident:" << std::endl;
    std::cout << "1. Medical emergency" << std::endl;
    std::cout << "2. Security threat" << std::endl;
    std::cout << "3. Facilities issue" << std::endl;
    std::cout << "4. Lockdown" << std::endl;


    int selection = 0;
    std::cin >> selection;
    std::cin.ignore();

    std::string incidentType;
    switch (selection) {
        case 1:
            incidentType = "medical";
            break;
        case 2:
            incidentType = "security";
            break;
        case 3:
            incidentType = "facilities";
            break;
        case 4:
            incidentType = "lockdown";
            break;
        default:
            incidentType = "security";
            break;
    }

    std::string location;
    std::cout << "Location: ";
    std::getline(std::cin, location);
    if (location.empty()) {
        location = "Engineering block";
    }

    EmergencyMediator emergencyMediator(incidentType, location);

    AccessControlSystem accessControl;
    CommunicationService comms;
    MedicalResponder medic;
    SecurityTeam security;
    VictimInterface victim;

    accessControl.reg(&emergencyMediator);
    comms.reg(&emergencyMediator);
    medic.reg(&emergencyMediator);
    security.reg(&emergencyMediator);
    victim.reg(&emergencyMediator);

    TriggerAlertCommand triggerAlert(&emergencyMediator);
    triggerAlert.execute();

    return 0;
}