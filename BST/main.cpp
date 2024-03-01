#include <iostream>
#include"IntensiveCareUnit.h"
#include"Patient.h"
#include<vector>
#include<fstream>
#include<chrono>
#include<list>
using namespace std;

int main()
{
    /*
    ifstream data("C:/Users/DELL/OneDrive/Bureau/pt.csv");
    if(data.is_open())
    {
        cout<<"file opened successfully\n";
    }
    IntensiveCareUnit unit("Cardiology");
    string name;
    long int id ;
    unsigned int age;
    char gender;
    bloodPressure bloodp;
    int heartRate;
    Time t;
    string pState;
    state st;
    Patient* p;
    auto start = chrono::steady_clock::now();
    while(data.peek()!=EOF)
    {
        p = new Patient();
        data.ignore(9999999999,'\n');

        getline(data,name,',');
        data>>id;
        data.ignore(1,',');
        data>>gender;
        data.ignore(1,',');
        data>>age;
        data.ignore(1,',');
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
        data>>pState;
        if(pState=="released")
        {
            st=released;
        }
        p->setName(name);
        p->setGender(gender);
        p->setAge(age);
        p->setId(id);
        p->setInfoMed(t,bloodp,heartRate);
        p->setState(st);
        unit.admitPatient(*p);


    }
    auto end = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds"<<endl;
	cout << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds"<<endl;
	cout << chrono::duration_cast<chrono::seconds>(end-start).count() << " seconds";
    unit.printPatients();
    const vector<infoMed>pHistory = p->getHistory();
    for(auto i= pHistory.begin();i!=pHistory.end();i++)
    {
        infoMed info = *i;
        cout<<info.bp.high<<"/"<<info.bp.low<<"\t"<<info.heartRate<<"\t"<<info.t.hour<<":"<<info.t.minute<<":"<<info.t.second<<"\n";
    }
    unit.setStateOfPatient(454322368,critical);
    cout<<"\n Critical list : \n";
    unit.displayCritical();
    cout<<"\nPrint new list :\n";
    unit.printPatients();
    */
    IntensiveCareUnit unit("Cardiology");
    auto start = chrono::steady_clock::now();
    unit.readFromFile("C:/Users/DELL/OneDrive/Bureau/pt.csv");
    auto end = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds"<<endl;
	cout << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds"<<endl;
	cout << chrono::duration_cast<chrono::seconds>(end-start).count() << " seconds"<<endl<<endl;
    Patient p = unit.findPatient(454322368);
    cout<<"Patient history : \n";
    p.printHistory();
    unit.printPatients();
    unit.setStateOfPatient(454322368,critical);
    cout<<"\n Critical list : \n";
    unit.displayCritical();
    cout<<"\nPrint new list :\n";
    unit.printPatients();
    return 0;
}
