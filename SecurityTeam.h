#ifndef SECURITYTEAM_H
#define SECURITYTEAM_H

#include "ResponseComponent.h"

class SecurityTeam: public ResponseComponent{

 SecurityTeam();
void receiveEmergencyMessage(int myId,std::string em) override;
void sendResponse() override;

};


#endif