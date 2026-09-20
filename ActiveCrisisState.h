#ifndef ACTIVECRISISSTATE_H
#define ACTIVECRISISSTATE_H

#include "IncidentState.h"

class ActiveCrisisState : public IncidentState
{
public:
    virtual ~ActiveCrisisState() {}

    std::string getStateName() const override;

    void validateStatus(const Incident& incident) const override;
    void evaluatePermissions(const Incident& incident) const override;

    void activate(Incident& incident) override;
    void resolve(Incident& incident) override;

    bool canDeployResponders() const override;
    bool canLockdownZone() const override;
};
#endif