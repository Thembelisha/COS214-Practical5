#ifndef SECURITYTEAM_H
#define SECURITYTEAM_H

#include "ResponseComponent.h"

class SecurityTeam: public ResponseComponent{
public:
    SecurityTeam();
    void receiveEmergencyMessage(std::string myId,std::string em) override;
    void sendResponse() override;

};


#endif