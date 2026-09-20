#include "MedicalResponder.h"
#include "CampusMediator.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

MedicalResponder::MedicalResponder() : ResponseComponent() {
    this->myId = "medical-responder-1";
    this->setCategory("medical");
}

void MedicalResponder::receiveEmergencyMessage(std::string myId, std::string em) {
    std::cout << myId << " received emergency from " << em << std::endl;
    std::cout << "MedicalResponder: dispatching emergency care team to the reported location." << std::endl;
    std::cout << "MedicalResponder: Acknowledge and respond to the incident." << std::endl;
}

void MedicalResponder::sendResponse() {
    std::string toId;
    std::string msg;
    std::cout << "   Paramedic " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "Paramedic" << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (this->emergency != nullptr) {
        this->emergency->communicate(toId, myId + ": " + msg);
    }
}