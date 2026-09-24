#ifndef FACILITIESSTUFF_H
#define FACILITIESSTUFF_H

#include "ResponseComponent.h"

class FacilitiesStaff : public ResponseComponent{
public:
    FacilitiesStaff();
    void receiveEmergencyMessage(std::string myId,std::string em) override;
    void sendResponse() override;

};


#endif