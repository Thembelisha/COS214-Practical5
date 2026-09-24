#ifndef EMERGENCYCOMMAND_H
#define EMERGENCYCOMMAND_H


class EmergencyCommand{
public:
virtual void execute() =0;
virtual ~EmergencyCommand() {}
};


#endif