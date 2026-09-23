#include "UnpoweredConstructionZoneDecorator.h"

#include <algorithm>
#include <iostream>
#include <utility>

UnpoweredConstructionZoneDecorator::UnpoweredConstructionZoneDecorator(
    std::unique_ptr<EmergencyResponder> responder)
    : ResponderDecorator(std::move(responder))
{
}

void UnpoweredConstructionZoneDecorator::deployToZone(const std::string& zone)
{
    std::cout << "[Decorator] Activating portable lighting and thermal tracking." << std::endl;
    wrappedResponder().deployToZone(zone);
    std::cout << "[Decorator] Construction-barrier override enabled for " << zone << "." << std::endl;
}

int UnpoweredConstructionZoneDecorator::getClearanceLevel() const
{
    const int constructionZoneClearance = 4;
    return std::max(wrappedResponder().getClearanceLevel(), constructionZoneClearance);
}

std::string UnpoweredConstructionZoneDecorator::getCapabilities() const
{
    return wrappedResponder().getCapabilities()
        + ", portable lighting, thermal tracking, construction-barrier override";
}
