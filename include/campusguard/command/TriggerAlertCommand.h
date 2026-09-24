#ifndef TRIGGERALERTCOMMAND_H
#define TRIGGERALERTCOMMAND_H

#include "EmergencyCommand.h"


class EmergencyMediator;

class TriggerAlertCommand: public EmergencyCommand{

    public:
    TriggerAlertCommand(EmergencyMediator* em);
    void execute() override;

    private:
    EmergencyMediator* em;

};


#endif