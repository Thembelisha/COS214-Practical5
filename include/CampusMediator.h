#ifndef CAMPUSMEDIATOR_H
#define CAMPUSMEDIATOR_H

#include <string>
#include <vector>

#include "ResponseComponent.h"

class Participant
{
public:
    std::string id;
    ResponseComponent* resp;
};

class CampusMediator
{
public:
    CampusMediator(std::string loc, std::string em);
    virtual ~CampusMediator();

    std::string addParticipant(ResponseComponent* me);
    void notifyComponent(std::string emergency, std::string location);
    void notifyComponent();
    void notifyByCategory(
        const std::string& incidentType,
        const std::string& emergency,
        const std::string& location);
    void cancelEmergency();
    bool communicate(std::string id, std::string emergency);
    void removeParticipant(std::string id);
    void lockdown();
    void issueEvacuation(const std::string& instructions);

protected:
    std::vector<Participant*> participant;
    std::string emergency;
    std::string location;
};

#endif
