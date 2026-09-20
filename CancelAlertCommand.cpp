#include "CancelAlertCommand.h"
#include "EmergencyMediator.h"

CancelAlertCommand::CancelAlertCommand(EmergencyMediator* em) {
    this->em = em;
}

void CancelAlertCommand::execute(std::string emergency, std::string loc) {
    (void)emergency;
    (void)loc;
    if (this->em != nullptr) {
        this->em->cancelEmergency();
    }
}