#ifndef SIRENSENABLEDDECORATOR_H
#define SIRENSENABLEDDECORATOR_H

#include "ResponderDecorator.h"

class SirensEnabledDecorator : public ResponderDecorator
{
public:
    explicit SirensEnabledDecorator(std::unique_ptr<EmergencyResponder> responder);

    void deployToZone(const std::string& zone) override;
    int getClearanceLevel() const override;
    std::string getCapabilities() const override;
};

#endif
