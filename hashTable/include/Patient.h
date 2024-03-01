#ifndef PATIENT_H
#define PATIENT_H
#include<string>
#include<vector>
using namespace std;


// we used the following structures outside the class
//so they can be used by the other classes (IntensiveCareUnit for example)
// and we limit the risk of not using them as private , by using setters to enter them
struct Time
        {
           unsigned int hour;
           unsigned int minute;
           unsigned int second;

        };

    struct bloodPressure
        {
            unsigned int high;
            unsigned int low;
        };
    // structure that contains all the medical information of the patient
    struct infoMed
    {
        Time t; // time of taking measures
        bloodPressure bp;
        unsigned int heartRate; //positive value

    };
    // this indicates what is the medical state of the patient
    // the patient can be released for the intensive care unit
    // he can be dead
    // or its state can be critical
    // else he is included in the intensive care unit
    enum state
    {
        included = 0,
        released = 1,
        dead = -1,
        critical = 2
    };

class Patient
{
    friend ostream& operator <<(ostream& , const  Patient&);
private:
    string name;
    long int id;
    infoMed patientData;
    vector<infoMed> history;
    state pState;
    //additional information
    unsigned int age;
	string blood;
	char gender;

	//utility functions
	void setHour(const int &);
	void setMinute(const int &);
    void setSecond(const int &);
    void setHigh(const int &);
    void setLow(const int & );
    void setHeartRate(const unsigned int & );
    void setHistory();




public:
    // constructor
    // destructor
    Patient();
    Patient(const string & ,const long int &,const int & , const char &,const string&,const Time&, const bloodPressure&  , const int& );
    virtual ~Patient();
    //seters
    void setName(const string & );
    void setId(const long int &);
    void setAge(const unsigned int &);
    void setGender(const char &);
    void setBlood(const string &);
    void setTime(const int & , const int &, const int &);
    void setBloodPressure(const int &, const int &);
    void setInfoMed(const Time & , const bloodPressure & , const unsigned int &);
    void setState(const state &);
    bool operator ==(const Patient& )const;
    bool operator !=(const Patient &)const;
    void printHistory()const;
    //geters
    string getName() const;
    long int getId()const;
    unsigned int getAge()const;
    char getGender()const;
    string getBlood()const;
    Time getTime( )const;
    bloodPressure getBloodPressure()const;
    unsigned int getHeartRate()const;
    infoMed getInfoMed()const;// return the latest medical data of the patient
    state getState()const;
    const vector<infoMed> getHistory()const;




};
// adding hash functor to the class so we can use hash tables
namespace std{
template<>
class hash<Patient>
{
   public:
   size_t operator()( const Patient & p )
   {
     static hash<int> hf;
     return hf( p.getId( ) );// it uses the id to make hash
   }
};
}
#endif // PATIENT_H
