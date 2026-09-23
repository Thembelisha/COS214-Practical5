#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include "CampusMediator.h"

namespace {
std::string toLower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return text;
}
}

CampusMediator::CampusMediator(std::string loc, std::string em) {
    location = loc;
    emergency = em;
}

CampusMediator::~CampusMediator() {
    for (std::vector<Participant*>::iterator it = participant.begin(); it != participant.end(); ++it) {
        delete *it;
    }
    participant.clear();
}

std::string CampusMediator::addParticipant(ResponseComponent* me) {
    Participant* person = new Participant();
    person->resp = me;
    person->id = me->getId();
    participant.push_back(person);
    return person->id;
}

void CampusMediator::notifyComponent(std::string emergencyMessage, std::string locationMessage) {
    std::vector<Participant*>::iterator it;

    for (it = participant.begin(); it != participant.end(); ++it) {
        (*it)->resp->receiveEmergencyMessage((*it)->id, "Broadcast: " + emergencyMessage + " at this location " + locationMessage);
    }
}

void CampusMediator::notifyComponent() {
    notifyByCategory(emergency, emergency, location);
}

void CampusMediator::notifyByCategory(const std::string& incidentType, const std::string& emergencyMessage, const std::string& locationMessage) {
    std::string normalized = toLower(incidentType);
    std::vector<std::string> relevantTeams;

    if (normalized.find("medical") != std::string::npos || normalized.find("injury") != std::string::npos || normalized.find("injured") != std::string::npos) {
        relevantTeams = {"communication"};
    } else if (normalized.find("security") != std::string::npos || normalized.find("threat") != std::string::npos || normalized.find("lockdown") != std::string::npos || normalized.find("intruder") != std::string::npos) {
        relevantTeams = {"communication"};
    } else if (normalized.find("facility") != std::string::npos || normalized.find("maintenance") != std::string::npos || normalized.find("power") != std::string::npos || normalized.find("water") != std::string::npos) {
        relevantTeams = {"communication"};
    } else {
        relevantTeams = {"communication"};
    }

    for (std::vector<Participant*>::iterator it = participant.begin(); it != participant.end(); ++it) {
        std::string teamCategory = (*it)->resp->getCategory();
        if (std::find(relevantTeams.begin(), relevantTeams.end(), teamCategory) != relevantTeams.end()) {
            (*it)->resp->receiveEmergencyMessage((*it)->id, "Response needed: " + emergencyMessage + " at " + locationMessage);
        }
    }
}

bool CampusMediator::communicate(std::string _id, std::string emergencyMessage) {
    std::vector<Participant*>::iterator it;
    bool found = false;

    for (it = participant.begin(); it != participant.end() && !found; ++it) {
        if ((*it)->id == _id) {
            found = true;
            (*it)->resp->receiveEmergencyMessage(_id, emergencyMessage);
        }
    }
    return found;
}

void CampusMediator::removeParticipant(std::string idToRemove) {
    std::vector<Participant*>::iterator it;

    for (it = participant.begin(); it != participant.end(); ++it) {
        if ((*it)->id == idToRemove) {
            delete *it;
            participant.erase(it);
            break;
        }
    }
}

void CampusMediator::cancelEmergency() {
    std::cout << "The emergency has been resolved" << std::endl;
}

void CampusMediator::lockdown() {
    std::cout << "Campus lockdown initiated." << std::endl;
    //link a decorator here i think
}