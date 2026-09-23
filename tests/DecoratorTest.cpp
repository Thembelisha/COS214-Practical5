#include "BaseResponderUnit.h"
#include "EmergencyResponder.h"
#include "MedicalResponder.h"
#include "SecurityTeam.h"
#include "SirensEnabledDecorator.h"
#include "UnpoweredConstructionZoneDecorator.h"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

int main()
{
    std::unique_ptr<EmergencyResponder> basicSecurityUnit(
        new BaseResponderUnit("Test security unit", 2));
    std::unique_ptr<EmergencyResponder> constructionSecurityUnit(
        new UnpoweredConstructionZoneDecorator(std::move(basicSecurityUnit)));
    std::unique_ptr<EmergencyResponder> fullyEquippedSecurityUnit(
        new SirensEnabledDecorator(std::move(constructionSecurityUnit)));

    assert(fullyEquippedSecurityUnit->getClearanceLevel() == 4);
    assert(fullyEquippedSecurityUnit->getCapabilities().find("thermal tracking") != std::string::npos);
    assert(fullyEquippedSecurityUnit->getCapabilities().find("emergency sirens") != std::string::npos);

    SecurityTeam securityTeam(std::move(fullyEquippedSecurityUnit));
    securityTeam.receiveEmergencyMessage(
        "security-team-1", "Engineering construction zone");

    std::unique_ptr<EmergencyResponder> basicMedicalUnit(
        new BaseResponderUnit("Test medical unit", 3));
    std::unique_ptr<EmergencyResponder> priorityMedicalUnit(
        new SirensEnabledDecorator(std::move(basicMedicalUnit)));
    MedicalResponder medicalResponder(std::move(priorityMedicalUnit));
    medicalResponder.receiveEmergencyMessage(
        "medical-responder-1", "Engineering construction zone");

    bool rejectedNullResponder = false;
    try {
        std::unique_ptr<EmergencyResponder> missingResponder;
        SirensEnabledDecorator invalidDecorator(std::move(missingResponder));
    } catch (const std::invalid_argument&) {
        rejectedNullResponder = true;
    }

    assert(rejectedNullResponder);
    return 0;
}
