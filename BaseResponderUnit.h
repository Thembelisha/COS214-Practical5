#ifndef BASERESPONDERUNIT_H
#define BASERESPONDERUNIT_H

#include "EmergencyResponder.h"

#include <string>

class BaseResponderUnit : public EmergencyResponder
{
public:
    BaseResponderUnit(const std::string& unitName, int clearanceLevel);

    void deployToZone(const std::string& zone) override;
    int getClearanceLevel() const override;
    std::string getCapabilities() const override;

private:
    std::string unitName;
    int clearanceLevel;
};

#endif
