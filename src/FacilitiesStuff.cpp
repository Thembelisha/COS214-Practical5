#include "FacilitiesStuff.h"
#include "CampusMediator.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

FacilitiesStuff::FacilitiesStuff() : ResponseComponent() {
    this->myId = "facilities-team-1";
    this->setCategory("facilities");
    std::cout << "faculty team responding to incident" << std::endl;
}

void FacilitiesStuff::receiveEmergencyMessage(std::string myId, std::string em) {
    std::cout << myId << " received emergency from " << em << std::endl;
    std::cout << "FacilitiesStuff: Acknowledge and respond to the incident." << std::endl;
}

void FacilitiesStuff::sendResponse() {
    std::string toId;
    std::string msg;
    std::cout << "fuculty " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "fuculty" << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (this->emergency != nullptr) {
        this->emergency->communicate(toId, myId + ": " + msg);
    }
}