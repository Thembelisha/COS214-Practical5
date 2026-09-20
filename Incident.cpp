#include "Incident.h"
#include "ReportedState.h"
#include <iostream>

using namespace std;

Incident::Incident( int incidentId,const std::string& location,const std::string& description)
:incidentID(incidentId),location(location),description(description),currentState(new ReportedState())
{
    cout<<"Incident #"<<incidentID<<"reported at"<< location <<endl; 
}
Incident::~Incident()
{
    delete currentState;
}
int Incident::getId()const
{
    return incidentID;
}
string Incident::getLocation() const
{
    return location;
}
string Incident::getDescription() const
{
    return description;
}
string Incident::getStateName() const
{
    return currentState->getStateName();
}
void Incident::setState(IncidentState* nState)
{
    if(!nState)
    {
        cout<<"Cannot assign a null incident state."<<endl;
        return;
    }
    cout << "[STATE] Incident #" << incidentID<< ": " << currentState->getStateName()<< " -> " << nState->getStateName()<<endl;
    delete currentState;
    currentState=nState;
}
void Incident::activateCrisis()
{
    currentState->activate(*this);
}
void Incident::resolveIncident()
{
    currentState->resolve(*this);
}
void Incident::validateStatus()const
{
    currentState->validateStatus(*this);
}
void Incident::evaluatePermissions() const
{
    currentState->evaluatePermissions(*this);
}

bool Incident::canDeployResponders() const
{
    return currentState->canDeployResponders();
}

bool Incident::canLockdownZone() const
{
    return currentState->canLockdownZone();
}