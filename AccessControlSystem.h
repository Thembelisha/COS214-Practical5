#ifndef ACCESSCONTROLSYSTEM_H
#define ACCESSCONTROLSYSTEM_H

#include <string>

#include "ResponseComponent.h"

class AccessControlSystem: public ResponseComponent{

AccessControlSystem();
void receiveEmergencyMessage(int myId,std::string em) override;
void sendResponse() override;


};


#endif