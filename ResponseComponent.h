#ifndef RESPONSECOMPONENT_H
#define RESPONSECOMPONENT_H

#include <string>
class CampusMediator;


class ResponseComponent{

public:
    ResponseComponent();
    virtual void receiveEmergencyMessage(std::string myId, std::string em) = 0;
    virtual void sendResponse() = 0;
    void reg(CampusMediator* em);
    void cancel();
    std::string getId() const;
    void setId(const std::string& id);
    std::string getCategory() const;
    void setCategory(const std::string& category);
    virtual ~ResponseComponent();

protected:
    CampusMediator* emergency;
    std::string myId;
    std::string category;

};






#endif




