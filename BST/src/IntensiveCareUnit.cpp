#include "IntensiveCareUnit.h"
#include<list>
#include<fstream>

list<CriticalPatient>IntensiveCareUnit::criticalCareUnit = list<CriticalPatient> ();

IntensiveCareUnit::IntensiveCareUnit(const string& name )
{
    service = name;
}

IntensiveCareUnit::~IntensiveCareUnit()
{
    monitoringSystem.makeEmpty();
}
bool IntensiveCareUnit::admitPatient(const Patient& p)
{
    // we insert only if the patient is included
    if(p.getState()==included)
    {
        monitoringSystem.insert(p);
    }

}
Patient IntensiveCareUnit::findPatient(const long int& id)
{
    Patient temp ;// create temporary patient that have the id so we can do the research
    temp.setId(id);
    if(monitoringSystem.contains(temp))
    {
        return monitoringSystem.getX(temp);
    }
    else{cout<<"\nPatient does not exist \n";}
}
void IntensiveCareUnit::setStateOfPatient( const long int& id ,const state& s)
{
    Patient p = findPatient(id);
    p.setState(s);
    if(s == dead || s == released)
    {
        monitoringSystem.remove(p);
    }
    else if(s==critical)
    {
        CriticalPatient patient;
        patient.p = p;
        patient.serviceName = service;
        insertToCritical(patient);
        monitoringSystem.remove(p);

    }
}
//insert patient to critical care unit
void IntensiveCareUnit::insertToCritical(const CriticalPatient& p)
{
    criticalCareUnit.push_front(p);
}
void IntensiveCareUnit::printPatients()
{
    monitoringSystem.printTree();
}
// display the patients of the critical care unit
void IntensiveCareUnit::displayCritical()
{
    for(auto i = criticalCareUnit.begin(); i!= criticalCareUnit.end();i++)
    {
        CriticalPatient patient  =(*i);
        cout<<patient.p;
        cout<<"\nThis patient is from "<<patient.serviceName<<endl<<endl;
    }
}
void IntensiveCareUnit::readFromFile(const string & path)
{
    ifstream data(path);
    if(data.is_open())
    {
        cout<<"file opened successfully\n";
    }
    // the data that will be read
    string name;
    long int id ;
    unsigned int age;
    char gender;
    string blood;
    bloodPressure bloodp;
    int heartRate;
    Time t;
    string serviceName;
    Patient* p;
    while(data.peek()!=EOF)
    {
        p = new Patient();
        // ignore the line of titles
        data.ignore(9999999999,'\n');
        getline(data,serviceName,',');
        // if patient is in the service read its data
        if(service==serviceName)
        {
            getline(data,name,',');
            data>>id;
            data.ignore(1,',');
            data>>gender;
            data.ignore(1,',');
            data>>age;
            data.ignore(1,',');
            getline(data,blood,',');
            data>>bloodp.high;
            data.ignore(1,'/');
            data>>bloodp.low;
            data.ignore(1,',');
            data>>heartRate;
            data.ignore(1,',');
            data>>t.hour;
            data.ignore(1,':');
            data>>t.minute;
            data.ignore(1,':');
            data>>t.second;
            data.ignore(1,',');

            // set data
            p->setName(name);
            p->setGender(gender);
            p->setAge(age);
            p->setBlood(blood);
            p->setId(id);
            p->setInfoMed(t,bloodp,heartRate);
            admitPatient(*p);
        }
        // else jump line to read the data of the next patient
        else{
            data.ignore(9999999999,'\n');
        }

    }
}
