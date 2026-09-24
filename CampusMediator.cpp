#include "CampusMediator.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

namespace {
std::string toLower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return text;
}

bool receivesEvacuationInstruction(const std::string& category)
{
    return category == "communication"
        || category == "security"
        || category == "medical"
        || category == "facilities"
        || category == "victim";
}
}

CampusMediator::CampusMediator(std::string loc, std::string em)
    : emergency(em), location(loc)
{
}

CampusMediator::~CampusMediator()
{
    for (std::vector<Participant*>::iterator it = participant.begin();
         it != participant.end(); ++it) {
        delete *it;
    }
}

std::string CampusMediator::addParticipant(ResponseComponent* me)
{
    if (me == nullptr) {
        return "";
    }

    Participant* person = new Participant();
    person->resp = me;
    person->id = me->getId();
    participant.push_back(person);
    return person->id;
}

void CampusMediator::notifyComponent(
    std::string emergencyMessage, std::string locationMessage)
{
    for (std::vector<Participant*>::iterator it = participant.begin();
         it != participant.end(); ++it) {
        (*it)->resp->receiveEmergencyMessage(
            (*it)->id,
            "Broadcast: " + emergencyMessage + " at this location " + locationMessage);
    }
}

void CampusMediator::notifyComponent()
{
    notifyByCategory(emergency, emergency, location);
}

void CampusMediator::notifyByCategory(
    const std::string& incidentType,
    const std::string& emergencyMessage,
    const std::string& locationMessage)
{
    const std::string normalized = toLower(incidentType);
    std::vector<std::string> relevantTeams;

    if (normalized.find("medical") != std::string::npos
        || normalized.find("injury") != std::string::npos
        || normalized.find("injured") != std::string::npos) {
        relevantTeams.push_back("communication");
    } else if (normalized.find("security") != std::string::npos
               || normalized.find("threat") != std::string::npos
               || normalized.find("lockdown") != std::string::npos
               || normalized.find("intruder") != std::string::npos) {
        relevantTeams.push_back("communication");
    } else if (normalized.find("facility") != std::string::npos
               || normalized.find("facilities") != std::string::npos
               || normalized.find("maintenance") != std::string::npos
               || normalized.find("power") != std::string::npos
               || normalized.find("water") != std::string::npos) {
        relevantTeams.push_back("communication");
    } else {
        relevantTeams.push_back("communication");
    }

    for (std::vector<Participant*>::iterator it = participant.begin();
         it != participant.end(); ++it) {
        const std::string teamCategory = (*it)->resp->getCategory();
        if (std::find(relevantTeams.begin(), relevantTeams.end(), teamCategory)
            != relevantTeams.end()) {
            (*it)->resp->receiveEmergencyMessage(
                (*it)->id,
                "Response needed: " + emergencyMessage + " at " + locationMessage);
        }
    }
}

bool CampusMediator::communicate(
    std::string id, std::string emergencyMessage)
{
    for (std::vector<Participant*>::iterator it = participant.begin();
         it != participant.end(); ++it) {
        if ((*it)->id == id) {
            (*it)->resp->receiveEmergencyMessage(id, emergencyMessage);
            return true;
        }
    }
    return false;
}

void CampusMediator::removeParticipant(std::string idToRemove)
{
    for (std::vector<Participant*>::iterator it = participant.begin();
         it != participant.end(); ++it) {
        if ((*it)->id == idToRemove) {
            delete *it;
            participant.erase(it);
            break;
        }
    }
}

void CampusMediator::cancelEmergency()
{
    std::cout << "The emergency has been resolved" << std::endl;
}

void CampusMediator::lockdown()
{
    std::cout << "Campus lockdown initiated." << std::endl;
}

void CampusMediator::issueEvacuation(const std::string& instructions)
{
    if (instructions.empty()) {
        std::cout << "[Mediator] Empty evacuation instructions rejected."
                  << std::endl;
        return;
    }

    std::cout << "[Mediator] Coordinating evacuation: "
              << instructions << std::endl;

    for (std::vector<Participant*>::iterator it = participant.begin();
         it != participant.end(); ++it) {
        ResponseComponent* component = (*it)->resp;
        if (component != nullptr
            && receivesEvacuationInstruction(component->getCategory())) {
            component->receiveEmergencyMessage(
                (*it)->id, "Evacuation instruction: " + instructions);
        }
    }
}
