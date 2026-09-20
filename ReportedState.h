#ifndef REPORTEDSTATE_H
#define REPORTEDSTATE_H

#include "IncidentState.h"

class ReportedState : public IncidentState
{
public:
    virtual ~ReportedState() {}

    std::string getStateName() const ;

    void validateStatus(const Incident& incident) const ;
    void evaluatePermissions(const Incident& incident) const ;

    void activate(Incident& incident) ;
    void resolve(Incident& incident) ;

    bool canDeployResponders() const ;
    bool canLockdownZone() const ;
};

#endif