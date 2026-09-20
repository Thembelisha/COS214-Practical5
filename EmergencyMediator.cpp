#include "EmergencyMediator.h"

EmergencyMediator::EmergencyMediator(std::string _em, std::string _loc)
    : CampusMediator(_loc, _em) {
    em = _em;
    loc = _loc;
}

