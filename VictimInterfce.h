#ifndef VICTIMINTERFACE_H
#define VICTIMINTERFACE_H

#include "ResponseComponent.h"

class VictimInterface: public ResponseComponent{

    
VictimInterface();
void receiveEmergencyMessage(int myId,std::string em) override;
void sendResponse() override;
};


#endif