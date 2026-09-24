#include "BaseResponderUnit.h"

#include <iostream>
#include <stdexcept>

BaseResponderUnit::BaseResponderUnit(const std::string& unitName, int clearanceLevel)
    : unitName(unitName), clearanceLevel(clearanceLevel)
{
    if (unitName.empty()) {
        throw std::invalid_argument("A responder unit must have a name.");
    }

    if (clearanceLevel < 0) {
        throw std::invalid_argument("A responder clearance level cannot be negative.");
    }
}

void BaseResponderUnit::deployToZone(const std::string& zone)
{
    std::cout << "[Responder] " << unitName << " deploying to " << zone << "." << std::endl;
}

int BaseResponderUnit::getClearanceLevel() const
{
    return clearanceLevel;
}

std::string BaseResponderUnit::getCapabilities() const
{
    return "standard emergency-response equipment";
}
