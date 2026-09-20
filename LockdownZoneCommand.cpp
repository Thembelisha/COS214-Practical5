#include "LockdownZoneCommand.h"

  LockdownZoneCommand::LockdownZoneCommand(EmergencyMediator* em){
    this->em=em;
 }
    void  LockdownZoneCommand::execute() {
        em->lockdown();
    }