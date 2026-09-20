#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

using namespace std;

string ResolvedState::getStateName()const
{
    return "Resolved";
}
void ResolvedState::validateStatus(const Incident& incident) const
{
    cout<<"[STATE] Incident #"<< incident.getId()<<"has been resolved"<<endl;
}
void ResolvedState:: evaluatePermissions(const Incident&) const
{
    cout<<"[PERMISSION] Emergency permissions disabled."<<"Normal campus operations restored."<<endl;

}
void ResolvedState::activate(Incident& incident)
{
    cout<<"[WARNING] Cannot reactivate resolved incident # "<<incident.getId()<<", A newincident must be registered."<<endl;
}
void ResolvedState:: resolve(Incident& incident)
{
    cout<<"[WARNING] Incident #"<< incident.getId()<<" is already resolved."<<endl;
}
bool ResolvedState::canDeployResponders() const
{
    return false;
}

bool ResolvedState::canLockdownZone() const
{
    return false;
}