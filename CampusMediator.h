#ifndef CAMPUSMEDIATOR_H
#define CAMPUSMEDIATOR_H

#include <string>
#include <vector>

#include "ResponseComponent.h"

class Participant {
  public:
    std::string id;
    ResponseComponent*  resp;
};

class CampusMediator{

public:
    CampusMediator(std::string loc,std::string em);
    void addParticipant(Participant* me);
    void notifyComponent(std::string emergency,std::string location);
    void notifyComponent();
    void notifyByCategory(const std::string& incidentType, const std::string& emergency, const std::string& location);
    void cancelEmergency();
    bool communicate(std::string _id,std::string emergency);
    void removeParticipant(std::string);
    void lockdown();

protected:
        std::vector<Participant* >participant;
        std::string emergency;
        std::string location;

};


#endif