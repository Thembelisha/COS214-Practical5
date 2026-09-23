#include "MedicalResponder.h"

#include "BaseResponderUnit.h"
#include "CampusMediator.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

MedicalResponder::MedicalResponder()
    : MedicalResponder(std::unique_ptr<EmergencyResponder>(
          new BaseResponderUnit("Campus medical unit", 3)))
{
}

MedicalResponder::MedicalResponder(std::unique_ptr<EmergencyResponder> responder)
    : ResponseComponent(), responder(std::move(responder))
{
    if (!this->responder) {
        throw std::invalid_argument("MedicalResponder requires a responder unit.");
    }

    myId = "medical-responder-1";
    setCategory("medical");
}

void MedicalResponder::receiveEmergencyMessage(std::string myId, std::string em)
{
    std::cout << myId << " received emergency from " << em << std::endl;
    std::cout << "MedicalResponder capabilities: " << responder->getCapabilities()
              << " (clearance " << responder->getClearanceLevel() << ")" << std::endl;
    responder->deployToZone(em);
    std::cout << "MedicalResponder: dispatching emergency care team to the reported location." << std::endl;
    std::cout << "MedicalResponder: Acknowledge and respond to the incident." << std::endl;
}

void MedicalResponder::sendResponse()
{
    std::string toId;
    std::string msg;
    std::cout << "Paramedic " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "Paramedic " << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (emergency != nullptr) {
        emergency->communicate(toId, myId + ": " + msg);
    }
}
