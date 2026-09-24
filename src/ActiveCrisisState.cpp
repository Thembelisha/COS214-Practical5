#include "ActiveCrisisState.h"
#include "ResolvedState.h"
#include "Incident.h"

string ActiveCrisisState::getStateName()const
{
    return "Active Crisis";
}
void ActiveCrisisState::validateStatus(const Incident& incident) const
{
    std::cout<<"[State] Incident #"<<incident.getId()<<" is currently an ACTIVE CRISIS."<<endl;

}
void ActiveCrisisState::evaluatePermissions(const Incident&) const
{
    cout<<"[PERMISSION] Emergency responder deployment,"<< "tracking overrides and perimeter lockdown are enabled"<< endl;

}
void ActiveCrisisState:: activate(Incident& incident)
{
    cout<< "[WARNING] Incident #"<< incident.getId()<<"is already an active crisis."<< endl;
}
void ActiveCrisisState::resolve(Incident& incident)
{
    cout<<"[STATE] emergency operations are standing down"<<endl;
    incident.setState(new ResolvedState());
}
bool ActiveCrisisState::canDeployResponders() const
{
    return true;
}
bool ActiveCrisisState::canLockdownZone()const
{
    return true;
}