#include "EvacuationInstructionDecorator.h"

#include "CampusMediator.h"

#include <stdexcept>
#include <utility>

EvacuationInstructionDecorator::EvacuationInstructionDecorator(
    std::unique_ptr<EmergencyCommand> wrappedCommand,
    CampusMediator& mediator,
    const std::string& instructions)
    : EmergencyCommandDecorator(std::move(wrappedCommand)),
      mediator(mediator),
      instructions(instructions)
{
    if (instructions.empty()) {
        throw std::invalid_argument(
            "Evacuation instructions cannot be empty.");
    }
}

void EvacuationInstructionDecorator::execute()
{
    executeWrappedCommand();
    mediator.issueEvacuation(instructions);
}
