#ifndef ACCESSCONTROLSYSTEM_H
#define ACCESSCONTROLSYSTEM_H

#include <string>

#include "ResponseComponent.h"

class AccessControlSystem: public ResponseComponent{
public:
    AccessControlSystem();
    void receiveEmergencyMessage(std::string myId,std::string em) override;
    void sendResponse() override;


};


#endif