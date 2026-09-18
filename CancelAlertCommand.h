#ifndef CANCELALERTCOMMAND_H
#define CANCELALERTCOMMAND_H

#include "EmergencyCommand.h"

class EmergencyMediator;

class CancelAlertCommand: public EmergencyCommand{

  public:
   CancelAlertCommand(EmergencyMediator* em);
    void execute() override;

    private:
    EmergencyMediator* em;

};


#endif