#ifndef EMERGENCYCOMMANDDECORATOR_H
#define EMERGENCYCOMMANDDECORATOR_H

#include "EmergencyCommand.h"

#include <memory>

class EmergencyCommandDecorator : public EmergencyCommand
{
public:
    explicit EmergencyCommandDecorator(
        std::unique_ptr<EmergencyCommand> wrappedCommand);
    virtual ~EmergencyCommandDecorator() {}

protected:
    void executeWrappedCommand();

private:
    std::unique_ptr<EmergencyCommand> wrappedCommand;
};

#endif
