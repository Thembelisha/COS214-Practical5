#ifndef VICTIMINTERFACE_H
#define VICTIMINTERFACE_H

#include "ResponseComponent.h"

class VictimInterface: public ResponseComponent{
public:
    VictimInterface();
    void receiveEmergencyMessage(std::string myId,std::string em) override;
    void sendResponse() override;
};


#endif