#ifndef EMERGENCYRESPONDER_H
#define EMERGENCYRESPONDER_H

#include <string>

class EmergencyResponder
{
public:
    virtual ~EmergencyResponder() {}

    virtual void deployToZone(const std::string& zone) = 0;
    virtual int getClearanceLevel() const = 0;
    virtual std::string getCapabilities() const = 0;
};

#endif
