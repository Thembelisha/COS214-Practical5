#include "OperatorInvoker.h"

OperatorInvoker::OperatorInvoker(EmergencyCommand* _alert,EmergencyCommand* lockdown,EmergencyCommand* no_alert){
    this->_alert=_alert;
    this->no_alert=no_alert;
    this->lockdown=lockdown;
}
void OperatorInvoker::alert()
{
    if (_alert != nullptr)
    {
      _alert->execute();
    }
}

void OperatorInvoker::noAlert()
{
    if (no_alert != nullptr)
    {
      no_alert->execute();
    }
}

void OperatorInvoker::lockDown()
{
    if (lockdown != nullptr)
    {
      lockdown->execute();
    }
}