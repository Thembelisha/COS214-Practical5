#include <iostream>
#include <vector>
#include "CampusMediator.h"

CampusMediator::CampusMediator(std::string loc,std::string em):nextId(0) {
    location=loc;
    emergency=em;
}

    int CampusMediator::addParticipant(ResponseComponent* me){
    Participant* person = new Participant();
  person->resp = me;
  person->id = nextId++;
  participant.push_back(person);
  std::cout<<person->id<<" has just registered."<<std::endl;
  return person->id;
    }
    void CampusMediator::notifyComponent(std::string emergency,std::string location){
        std::vector<Participant*>::iterator it;

        for (it = participant.begin(); it != participant.end(); ++it) {
    (*it)->resp->receiveMessage("Broadcast: "+emergency +"at this location"+location);
  }
}
 void CampusMediator::notifyComponent(){
    notifyComponent(em,loc);
 }


    
    bool CampusMediator::communicate(int _id,std::string emergency){

        vector<Participant*>::iterator it;
  bool found = false;

  it = participant.begin();
  while ((it != participant.end()) && (!found)) {
    if ((*it)->id == id) {
      found = true;
      (*it)->resp->receiveMessage(emergency);
    } else {
      it++;
    }
  }   
  return found;
    }
    void CampusMediator::removeParticipant(int){
    vector<Participant*>::iterator it;
    bool found = false;
    int count = 0;

  it = participant.begin();
  while ((it != participant.end()) && (!found)) {
    if ((*it)->id == id) {
      found = true;
    } else {
      it++;
      count++;
    }
  }   
  if (found) {
    cout<<(*it)->id<<" has just left."<<endl; 
    participant.erase(it);

  }



    }
void CampusMediator::cancelEmergency(){
    std::cout<<"The emergency has be resolved"<<std::endl;
}
void lockdown(){
    //i want to somehow connect this to the decorators
}