#ifndef CAMPUSMEDIATOR_H
#define CAMPUSMEDIATOR_H

#include <string>
#include <vector>

#include "ResponseComponent.h"

class Participant {
  public:
    int    id;
    ResponseComponent*  resp;
};

class CampusMediator{

public:
    CampusMediator(std::string loc,std::string em);
    int addParticipant(ResponseComponent* me);
    void notifyComponent(std::string emergency,std::string location);
    void cancelEmergency();
    bool communicate(int _id,std::string emergency);
    void removeParticipant(int);
    void lockdown();

protected:
        std::vector<Participant* >participant;
        int nextId;
        std::string emergency;
        std::string location;

};


#endif