#ifndef RESPONSECOMPONENT_H
#define RESPONSECOMPONENT_H

#include <string>
class CampusMediator;


class ResponseComponent{

public:
ResponseComponent();
virtual void receiveEmergencyMessage(int myId,std::string em) =0;
virtual void sendResponse() =0;
void reg(CampusMediator* em);
void cancel();
virtual ~ResponseComponent();

protected:
CampusMediator* emergency;
int myId;

};






#endif




