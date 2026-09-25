#include "CancelAlertCommand.h"
#include "EmergencyMediator.h"

CancelAlertCommand::CancelAlertCommand(EmergencyMediator* em) {
    this->em = em;
}

void CancelAlertCommand::execute() {
    if (this->em != nullptr) {
        this->em->cancelEmergency(); 
    }
}