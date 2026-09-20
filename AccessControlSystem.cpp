#include "AccessControlSystem.h"
#include "CampusMediator.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

AccessControlSystem::AccessControlSystem() : ResponseComponent() {
    this->myId = "access-control-1";
    this->setCategory("access");
}

void AccessControlSystem::receiveEmergencyMessage(std::string myId, std::string em) {
    std::cout << myId << " received emergency: " << em << std::endl;
    std::cout << "AccessControlSystem: locking doors and checking the nearest safe access points." << std::endl;
    std::cout << "AccessControlSystem: Acknowledge and respond to the incident." << std::endl;
}

void AccessControlSystem::sendResponse() {
    std::string toId;
    std::string msg;

    std::cout << "AccessControl " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "AccessControl " << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (this->emergency != nullptr) {
        this->emergency->communicate(toId, myId + ": " + msg);
    }
}
