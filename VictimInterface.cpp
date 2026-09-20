#include "VictimInterface.h"
#include <iostream>

VictimInterface::VictimInterface():ResponseComponent(){

std::cout<<"I am in need of help"<<std::endl;
}
void VictimInterface::receiveEmergencyMessage(int myId,std::string em) {
std::cout<<myId<<"received message  "<<em<<std::endl;
}
void VictimInterface::sendResponse(){
  string toId;
  string msg;
  cout<<"Student "<<myId<<" send message to? ";
  getline(cin,toId,'\n');

  cout<<"Student "<<myId<<" message? ";
  getline(cin,msg,'\n');

  ostringstream convert;
  convert << myId;
  CampusMediator->communicate(atoi(toId.c_str()),convert.str()+": "+msg);
}
