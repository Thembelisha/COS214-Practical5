#include "CancelAlertCommand.h"

  CancelAlertCommand::CancelAlertCommand(EmergencyMediator* em){

this->em=em;
 }
    void  CancelAlertCommand::execute(std::string em,std::string loc){

        em->cancelEmergency();
    }