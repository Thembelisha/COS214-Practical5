#include "SecurityTeam.h"
#include "CampusMediator.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

SecurityTeam::SecurityTeam() : ResponseComponent() {
    this->myId = "security-team-1";
    this->setCategory("security");
}

void SecurityTeam::receiveEmergencyMessage(std::string myId, std::string em) {
    std::cout << myId << " received emergency from " << em << std::endl;
    std::cout << "SecurityTeam: securing the area and checking nearby entrances." << std::endl;
    std::cout << "SecurityTeam: Acknowledge and respond to the incident." << std::endl;
}

void SecurityTeam::sendResponse() {
    std::string toId;
    std::string msg;
    std::cout << "Security " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "Security " << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (this->emergency != nullptr) {
        this->emergency->communicate(toId, myId + ": " + msg);
    }
}