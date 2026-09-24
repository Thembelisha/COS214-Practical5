#ifndef RESPONDERDECORATOR_H
#define RESPONDERDECORATOR_H

#include "EmergencyResponder.h"

#include <memory>

class ResponderDecorator : public EmergencyResponder
{
public:
    explicit ResponderDecorator(std::unique_ptr<EmergencyResponder> responder);
    virtual ~ResponderDecorator() {}

protected:
    EmergencyResponder& wrappedResponder();
    const EmergencyResponder& wrappedResponder() const;

private:
    std::unique_ptr<EmergencyResponder> responder;
};

#endif
