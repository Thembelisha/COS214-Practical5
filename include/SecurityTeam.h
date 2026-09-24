#ifndef SECURITYTEAM_H
#define SECURITYTEAM_H

#include "EmergencyResponder.h"
#include "ResponseComponent.h"

#include <memory>

class SecurityTeam : public ResponseComponent
{
public:
    SecurityTeam();
    explicit SecurityTeam(std::unique_ptr<EmergencyResponder> responder);

    void receiveEmergencyMessage(std::string myId, std::string em) override;
    void sendResponse() override;

private:
    std::unique_ptr<EmergencyResponder> responder;
};

#endif
