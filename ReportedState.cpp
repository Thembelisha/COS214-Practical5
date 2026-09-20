#include "ReportedState.h"
#include "ActiveCrisisState.h"
#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

using namespace std;

string ReportedState::getStateName()const
{
    return "Reported";
}
void ReportedState::validateStatus(const Incident& incident) const
{
    cout << "[STATE] Incident #" << incident.getId()<< " is awaiting crisis verification."<< std::endl;
}
void ReportedState::evaluatePermissions(const Incident&) const
{
    cout<< "[PERMISSION] Emergency deployment and wide lockdown "<< "are restricted while incident is only reported."<< std::endl;
}
void ReportedState::activate(Incident& incident)
{
    cout<<"[state] incident verified as an active crisis."<<endl;
    incident.setState( new ActiveCrisisState());
}
void ReportedState:: resolve(Incident& incident)
{
    cout << "[STATE] Report cancelled before active deployment."<< std::endl;
    incident.setState(new ResolvedState());
}
bool ReportedState:: canDeployResponders() const
{
    return false;
}
bool ReportedState::canLockdownZone() const
{
    return false;
}