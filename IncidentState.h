#ifndef INCIDENTTSTATE_H
#define INCIDENTTSTATE_H
#include <iostream>
using namespace std;

class Incident;
class IncidentState
{
    public:
        virtual string getStateName()const=0;
        virtual void validateStatus(const Incident & incident) const=0;
        virtual void evaluatePermissions(const Incident& incident)const=0;
        virtual void activate(Incident& incident)=0;
        virtual void resolve(Incident& incident)=0;
        virtual bool canDeployResponders()const=0;
        virtual bool canLockdownZone() const=0;
        virtual ~IncidentState(){};
};
#endif