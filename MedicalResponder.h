#ifndef MEDICALRESPONDER_H
#define MEDICALRESPONDER_H

#include "ResponseComponent.h"

class MedicalResponder: public ResponseComponent{
public:
    MedicalResponder();
    void receiveEmergencyMessage(std::string myId,std::string em) override;
    void sendResponse() override;

};


#endif