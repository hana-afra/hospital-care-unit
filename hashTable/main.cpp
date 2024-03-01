#include <iostream>
#include"IntensiveCareUnit.h"
#include<fstream>
#include<chrono>
using namespace std;

int main()
{
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
