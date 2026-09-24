#ifndef CAMPUSEMERGENCYFACADE_H
#define CAMPUSEMERGENCYFACADE_H

class Incident;
class OperatorInvoker;
class EmergencyMediator;

class CampusEmergencyFacade
{
private:
    Incident& incident;
    OperatorInvoker& invoker;
    EmergencyMediator& mediator;

public:
    CampusEmergencyFacade(Incident& incident,OperatorInvoker& invoker,EmergencyMediator& mediator);
    
    void handlePanicAlert();

    void resolveEmergency();

    void showIncidentStatus() const;
    void lockdownZone();
};

#endif