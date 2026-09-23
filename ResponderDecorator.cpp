#include "ResponderDecorator.h"

#include <stdexcept>
#include <utility>

ResponderDecorator::ResponderDecorator(std::unique_ptr<EmergencyResponder> responder)
    : responder(std::move(responder))
{
    if (!this->responder) {
        throw std::invalid_argument("A responder decorator requires a responder to wrap.");
    }
}

EmergencyResponder& ResponderDecorator::wrappedResponder()
{
    return *responder;
}

const EmergencyResponder& ResponderDecorator::wrappedResponder() const
{
    return *responder;
}
