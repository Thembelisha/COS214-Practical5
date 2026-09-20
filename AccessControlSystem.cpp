#include "AccessControlSystem.h"
#include <iostream>

AccessControlSystem::AccessControlSystem():ResponseComponent(){

std::cout<<"AccessControlSystem to all locks on Campus"<<std::endl;
}
void receiveEmergencyMessage(int myId,std::string em) {
std::cout<<myId<<"received emergency  "<<em<<std::endl;
}
void sendResponse(){
  string toId;
  string msg;
  cout<<"AccessControl "<<myId<<" send message to? ";
  getline(cin,toId,'\n');

  cout<<"AccessControlt "<<myId<<" message? ";
  getline(cin,msg,'\n');

  ostringstream convert;
  convert << myId;
  CampusMediator->communicate(atoi(toId.c_str()),convert.str()+": "+msg);
}
