#include "EmergencyCommandDecorator.h"

#include <stdexcept>
#include <utility>

EmergencyCommandDecorator::EmergencyCommandDecorator(
    std::unique_ptr<EmergencyCommand> wrappedCommand)
    : wrappedCommand(std::move(wrappedCommand))
{
    if (!this->wrappedCommand) {
        throw std::invalid_argument(
            "An emergency command decorator requires a command to wrap.");
    }
}

void EmergencyCommandDecorator::executeWrappedCommand()
{
    wrappedCommand->execute();
}
