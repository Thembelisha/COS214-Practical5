#ifndef CANCELALERTCOMMAND_H
#define CANCELALERTCOMMAND_H

#include <string>
#include "EmergencyCommand.h"

class EmergencyMediator;

class CancelAlertCommand: public EmergencyCommand{

public:
    CancelAlertCommand(EmergencyMediator* em);
    void execute(std::string emergency,std::string loc);

private:
    EmergencyMediator* em;

};


#endif