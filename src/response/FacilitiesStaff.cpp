#include "FacilitiesStaff.h"
#include "CampusMediator.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

FacilitiesStaff::FacilitiesStaff() : ResponseComponent() {
    this->myId = "facilities-team-1";
    this->setCategory("facilities");
    std::cout << "Facilities team responding to incident" << std::endl;
}

void FacilitiesStaff::receiveEmergencyMessage(std::string myId, std::string em) {
    std::cout << myId << " received emergency from " << em << std::endl;
    std::cout << "FacilitiesStaff: Acknowledge and respond to the incident." << std::endl;
}

void FacilitiesStaff::sendResponse() {
    std::string toId;
    std::string msg;
    std::cout << "Facilities " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "Facilities" << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (this->emergency != nullptr) {
        this->emergency->communicate(toId, myId + ": " + msg);
    }
}