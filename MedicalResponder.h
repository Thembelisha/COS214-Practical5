#ifndef MEDICALRESPONDER_H
#define MEDICALRESPONDER_H

#include "EmergencyResponder.h"
#include "ResponseComponent.h"

#include <memory>

class MedicalResponder : public ResponseComponent
{
public:
    MedicalResponder();
    explicit MedicalResponder(std::unique_ptr<EmergencyResponder> responder);

    void receiveEmergencyMessage(std::string myId, std::string em) override;
    void sendResponse() override;

private:
    std::unique_ptr<EmergencyResponder> responder;
};

#endif
