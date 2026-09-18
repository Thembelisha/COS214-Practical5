#ifndef LOCKDOWNZONECOMMAND_H
#define LOCKDOWNZONECOMMAND_H

#include "EmergencyCommand.h"

class EmergencyMediator;

class LockdownZoneCommand: public EmergencyCommand{

  public:
   LockdownZoneCommand(EmergencyMediator* em);
    void execute() override;

    private:
    EmergencyMediator* em;

};





#endif