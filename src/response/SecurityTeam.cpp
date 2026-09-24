#include "SecurityTeam.h"

#include "BaseResponderUnit.h"
#include "CampusMediator.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

SecurityTeam::SecurityTeam()
    : SecurityTeam(std::unique_ptr<EmergencyResponder>(
          new BaseResponderUnit("Campus security unit", 2)))
{
}

SecurityTeam::SecurityTeam(std::unique_ptr<EmergencyResponder> responder)
    : ResponseComponent(), responder(std::move(responder))
{
    if (!this->responder) {
        throw std::invalid_argument("SecurityTeam requires a responder unit.");
    }

    myId = "security-team-1";
    setCategory("security");
}

void SecurityTeam::receiveEmergencyMessage(std::string myId, std::string em)
{
    std::cout << myId << " received emergency from " << em << std::endl;
    std::cout << "SecurityTeam capabilities: " << responder->getCapabilities()
              << " (clearance " << responder->getClearanceLevel() << ")" << std::endl;
    responder->deployToZone(em);
    std::cout << "SecurityTeam: securing the area and checking nearby entrances." << std::endl;
    std::cout << "SecurityTeam: Acknowledge and respond to the incident." << std::endl;
}

void SecurityTeam::sendResponse()
{
    std::string toId;
    std::string msg;
    std::cout << "Security " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "Security " << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (emergency != nullptr) {
        emergency->communicate(toId, myId + ": " + msg);
    }
}
