#include "LockdownZoneCommand.h"
#include "EmergencyMediator.h"

LockdownZoneCommand::LockdownZoneCommand(EmergencyMediator* em) {
    this->em = em;
}

void LockdownZoneCommand::execute() {
    if (this->em != nullptr) 
    {
        this->em->lockdown();
    }
}