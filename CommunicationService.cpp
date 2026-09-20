#include "CommunicationService.h"
#include "CampusMediator.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

CommunicationService::CommunicationService() : ResponseComponent() {
    this->myId = "communication-service-1";
    this->setCategory("communication");
}

void CommunicationService::receiveEmergencyMessage(std::string myId, std::string em) {
    
    std::cout << "CommunicationService: routing alert to the appropriate team." << std::endl;

    if (this->emergency == nullptr) {
        return;
    }

    std::string lowered = em;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });

    if (lowered.find("medical") != std::string::npos || lowered.find("injury") != std::string::npos || lowered.find("injured") != std::string::npos) {
        this->emergency->communicate("medical-responder-1", "CommunicationService: medical team dispatched to " + em);
    } else if (lowered.find("security") != std::string::npos || lowered.find("threat") != std::string::npos || lowered.find("lockdown") != std::string::npos || lowered.find("intruder") != std::string::npos) {
        this->emergency->communicate("security-team-1", "CommunicationService: security team dispatched to " + em);
        this->emergency->communicate("access-control-1", "CommunicationService: access controls locked for " + em);
    } else if (lowered.find("facility") != std::string::npos || lowered.find("maintenance") != std::string::npos || lowered.find("power") != std::string::npos || lowered.find("water") != std::string::npos) {
        this->emergency->communicate("facilities-team-1", "CommunicationService: facilities team dispatched to " + em);
    } else {
        this->emergency->communicate("security-team-1", "CommunicationService: security dispatched to " + em);
    }
}

void CommunicationService::sendResponse() {
    std::string toId;
    std::string msg;
    std::cout << "Communication services " << myId << " send message to? ";
    std::getline(std::cin, toId, '\n');

    std::cout << "Communication services " << myId << " message? ";
    std::getline(std::cin, msg, '\n');

    if (this->emergency != nullptr) {
        this->emergency->communicate(toId, myId + ": " + msg);
    }
}