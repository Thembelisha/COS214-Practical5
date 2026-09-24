#ifndef UNPOWEREDCONSTRUCTIONZONEDECORATOR_H
#define UNPOWEREDCONSTRUCTIONZONEDECORATOR_H

#include "ResponderDecorator.h"

class UnpoweredConstructionZoneDecorator : public ResponderDecorator
{
public:
    explicit UnpoweredConstructionZoneDecorator(std::unique_ptr<EmergencyResponder> responder);

    void deployToZone(const std::string& zone) override;
    int getClearanceLevel() const override;
    std::string getCapabilities() const override;
};

#endif
