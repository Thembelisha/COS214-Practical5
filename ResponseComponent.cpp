#include "ResponseComponent.h"
#include "CampusMediator.h"

ResponseComponent::ResponseComponent() {
    emergency = nullptr;
    myId = "unknown-responder";
}

void ResponseComponent::reg(CampusMediator* em) {
    emergency = em;
    myId = emergency->addParticipant(this);
}

void ResponseComponent::cancel() {
    if (emergency != nullptr) {
        emergency->removeParticipant(myId);
    }
}

std::string ResponseComponent::getId() const {
    return myId;
}

void ResponseComponent::setId(const std::string& id) {
    myId = id;
}

std::string ResponseComponent::getCategory() const {
    return category;
}

void ResponseComponent::setCategory(const std::string& newCategory) {
    category = newCategory;
}

ResponseComponent::~ResponseComponent() {
}