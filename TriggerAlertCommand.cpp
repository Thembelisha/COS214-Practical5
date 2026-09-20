#include "TriggerAlertCommand.h"
#include "EmergencyMediator.h"

TriggerAlertCommand::TriggerAlertCommand(EmergencyMediator* em) {
    this->em = em;
}

void TriggerAlertCommand::execute() {
    if (this->em != nullptr) {
        this->em->notifyComponent();
    }
}