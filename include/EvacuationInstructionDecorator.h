#ifndef EVACUATIONINSTRUCTIONDECORATOR_H
#define EVACUATIONINSTRUCTIONDECORATOR_H

#include "EmergencyCommandDecorator.h"

#include <memory>
#include <string>

class CampusMediator;

class EvacuationInstructionDecorator : public EmergencyCommandDecorator
{
public:
    EvacuationInstructionDecorator(
        std::unique_ptr<EmergencyCommand> wrappedCommand,
        CampusMediator& mediator,
        const std::string& instructions);

    void execute() override;

private:
    CampusMediator& mediator;
    std::string instructions;
};

#endif
