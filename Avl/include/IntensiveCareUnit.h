#ifndef INTENSIVECAREUNIT_H
#define INTENSIVECAREUNIT_H
#include"Patient.h"
#include"AvlTree.h"
#include<list>
#include<string>
// this struct for the patients who enters critical care unit
struct CriticalPatient
{
    string serviceName;// the name of the service that a patient came from
    Patient p;
};
class IntensiveCareUnit
{
    public:
        IntensiveCareUnit(const string&);
        bool admitPatient(const Patient&);
        Patient findPatient(const long int& );// it returns the patient so the nurse and doctor can have access to his info
        //the following function sets state of the patient
        // if doctor set state "dead" or "released" to the patient with the id specified
        //than he will be deleted automatically
        // else if the state is critical he will be send to the critical care unit and deleted form the intensive care unit
        void setStateOfPatient(const long int& , const state & );
        void printPatients();
        void readFromFile(const string &);// it reads the patient info form file
        static void displayCritical();
        virtual ~IntensiveCareUnit();


    private:

        string service; //service name
        AvlTree<Patient> monitoringSystem;
        static list<CriticalPatient>criticalCareUnit;
        static void insertToCritical(const CriticalPatient&);
};

#endif // INTENSIVECAREUNIT_H
