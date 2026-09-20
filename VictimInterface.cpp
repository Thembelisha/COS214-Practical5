#include "VictimInterface.h"
#include "CampusMediator.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

VictimInterface::VictimInterface() : ResponseComponent() {
    this->myId = "victim-interface-1";
    this->setCategory("victim");
}

void VictimInterface::receiveEmergencyMessage(std::string myId, std::string em) {
    (void)myId;
    (void)em;
}

void VictimInterface::sendResponse() {
    std::string toId;
    std::string msg;
    std::cout << "Student " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "Student " << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (this->emergency != nullptr) {
        this->emergency->communicate(toId, myId + ": " + msg);
    }
}
