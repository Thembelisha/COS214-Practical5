#ifndef FACILITIESSTUFF_H
#define FACILITIESSTUFF_H

#include "ResponseComponent.h"

class FacilitiesStuff : public ResponseComponent{
public:
    FacilitiesStuff();
    void receiveEmergencyMessage(std::string myId,std::string em) override;
    void sendResponse() override;

};


#endif