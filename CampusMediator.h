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
    CampusMediator(ResponseComponent*);
    int addParticipant(ResponseComponent*);
    void notifyComponent(std::string emergency,std::string location);
    bool communicate(int _id,std::string emergency);
    void removeParticipant(int);

protected:
        std::vector<Participant* >participant;
        int nextId;

};


#endif