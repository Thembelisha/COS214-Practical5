#include "ResponseComponent.h"

ResponseComponent(){
    emergency=0;
    myId=-1;
}
void reg(CampusMediator* em ){
    emergency=em;
    myId=emergency->addParticipant(this);
}
void cancel(){
    emergency->removeParticipant(myId);
}