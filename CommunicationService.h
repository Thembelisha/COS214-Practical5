#ifndef COMMUNICATIONSERVICE_H
#define COMMUNICATIONSERVICE_H

#include "ResponseComponent.h"

class CommunicationService : public ResponseComponent{
public:
    CommunicationService();
    void receiveEmergencyMessage(std::string myId,std::string em) override;
    void sendResponse() override;


};


#endif