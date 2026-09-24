#ifndef OPERATORINVOKER_H
#define OPERATORINVOKER_H

#include "EmergencyCommand.h"

class OperatorInvoker{
public:
  OperatorInvoker(EmergencyCommand* alert,EmergencyCommand* lockdown,EmergencyCommand* no_alert);
  void alert();
  void noAlert();
  void lockDown();


  private:
  EmergencyCommand* _alert;
  EmergencyCommand* no_alert;
  EmergencyCommand* lockdown;
};


#endif