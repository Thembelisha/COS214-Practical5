#include "SirensEnabledDecorator.h"

#include <iostream>
#include <utility>

SirensEnabledDecorator::SirensEnabledDecorator(std::unique_ptr<EmergencyResponder> responder)
    : ResponderDecorator(std::move(responder))
{
}

void SirensEnabledDecorator::deployToZone(const std::string& zone)
{
    std::cout << "[Decorator] Emergency sirens enabled; traffic-lane priority requested." << std::endl;
    wrappedResponder().deployToZone(zone);
}

int SirensEnabledDecorator::getClearanceLevel() const
{
    return wrappedResponder().getClearanceLevel();
}

std::string SirensEnabledDecorator::getCapabilities() const
{
    return wrappedResponder().getCapabilities() + ", emergency sirens, traffic-lane priority";
}
