#ifndef INCIDENT_H
#define INCIDENT_H
#include <iostream>
#include "IncidentState.h"

using namespace std;

class Incident
{
    public:
        Incident(int incidentID,const string& location,const string& description);
        ~Incident();
        int getId()const;
        string getLocation()const;
        string getDescription() const;
        string getStateName() const;
        void setState(IncidentState* newState);
        void activateCrisis();
        void resolveIncident();
        void validateStatus() const;
        void evaluatePermissions() const;
        bool canDeployResponders() const;
        bool canLockdownZone() const;
    
    private:
        int incidentID;
        string location;
        string description;
        IncidentState* currentState;

};

#endif