#ifndef EMERGENCYMEDIATOR_H
#define EMERGENCYMEDIATOR_H

#include "CampusMediator.h"
#include <string>

class EmergencyMediator : public CampusMediator {
public:
    EmergencyMediator(std::string em,std::string loc);

protected:
    std::string em;
    std::string loc;
};


#endif 