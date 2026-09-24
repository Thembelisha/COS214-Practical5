#include "CommunicationService.h"

#include "CampusMediator.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

CommunicationService::CommunicationService() : ResponseComponent()
{
    myId = "communication-service-1";
    setCategory("communication");
}

void CommunicationService::receiveEmergencyMessage(
    std::string myId, std::string em)
{
    std::cout << "CommunicationService " << myId
              << ": routing alert." << std::endl;

    std::string lowered = em;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });

    if (lowered.find("evacuation instruction") != std::string::npos) {
        std::cout << "CommunicationService: broadcasting " << em << std::endl;
        return;
    }

    if (emergency == nullptr) {
        return;
    }

    if (lowered.find("medical") != std::string::npos
        || lowered.find("injury") != std::string::npos
        || lowered.find("injured") != std::string::npos) {
        emergency->communicate(
            "medical-responder-1",
            "CommunicationService: medical team dispatched to " + em);
    } else if (lowered.find("security") != std::string::npos
               || lowered.find("threat") != std::string::npos
               || lowered.find("lockdown") != std::string::npos
               || lowered.find("intruder") != std::string::npos) {
        emergency->communicate(
            "security-team-1",
            "CommunicationService: security team dispatched to " + em);
        emergency->communicate(
            "access-control-1",
            "CommunicationService: access controls locked for " + em);
    } else if (lowered.find("facility") != std::string::npos
               || lowered.find("facilities") != std::string::npos
               || lowered.find("maintenance") != std::string::npos
               || lowered.find("power") != std::string::npos
               || lowered.find("water") != std::string::npos) {
        emergency->communicate(
            "facilities-team-1",
            "CommunicationService: facilities team dispatched to " + em);
    } else {
        emergency->communicate(
            "security-team-1",
            "CommunicationService: security dispatched to " + em);
    }
}

void CommunicationService::sendResponse()
{
    std::string toId;
    std::string msg;
    std::cout << "Communication services " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "Communication services " << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (emergency != nullptr) {
        emergency->communicate(toId, myId + ": " + msg);
    }
}
