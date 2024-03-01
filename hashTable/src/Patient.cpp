#include "Patient.h"
#include<vector>
#include<iostream>
using namespace std;
Patient::Patient()
{
    name="";
    age = 0;
    id =0;
    gender=' ';
    setTime(0,0,0);
    setBloodPressure(0,0);
    setHeartRate(0);
    setState(included);

}
Patient::Patient(const string &pName,const long int & pId,const int & pAge, const char & pGender, const string& pBlood,
                 const Time&tim, const bloodPressure& b , const int& hrtRate)
{
    setName(pName);
    setAge(pAge);
    setId(pId);
    setGender(pGender);
    setBlood(pBlood);
    setTime(tim.hour,tim.minute,tim.second);
    setBloodPressure(b.high,b.low);
    setHeartRate(hrtRate);
    setInfoMed(tim,b,hrtRate);
    setState(included);// the state is set included automatically
                       //because  if patient is not included , than he is not a patient
}

Patient::~Patient()
{
    history.clear();
}
void Patient::setName(const string & pName )
{
    name = pName;
}
void Patient::setId(const long int & pId)
{
    id = pId;
}
void Patient::setAge(const unsigned int & pAge)
{
    age = pAge;
}
void Patient::setGender(const char & pGender)
{
    if( pGender =='F' ||pGender =='f' || pGender=='m' ||pGender=='M' )
    {
        gender = pGender;
    }
}
void Patient::setBlood(const string & pBlood)
{
    if(pBlood =="A+"||pBlood =="a+"||pBlood =="A-"||pBlood =="a-"||
        pBlood =="B+"||pBlood =="b+"||pBlood =="B-"||pBlood =="b-"||
        pBlood =="AB+"||pBlood =="ab+"||pBlood =="AB-"||pBlood =="ab-"||
        pBlood =="O+"||pBlood =="o+"||pBlood =="O-"||pBlood =="o-")
      {
          blood = pBlood;
      }
}
void Patient::setTime(const int & hours  , const int & minut, const int & sec)
{
    setHour(hours);
    setMinute(minut);
    setSecond(sec);
}

void Patient::setBloodPressure(const int & bloodhigh, const int & bloodlow)
{
    setHigh(bloodhigh);
    setLow(bloodlow);
}
void Patient::setInfoMed(const Time & t , const bloodPressure & pressure , const unsigned int & heartRate)
{
   setTime(t.hour,t.minute,t.second);
   setBloodPressure(pressure.high,pressure.low);
   setHeartRate(heartRate);
   setHistory();// each time we change the medical information of patient , we push it into the vector of history


}
void Patient::setHistory()
{
    history.push_back(patientData);
}
void Patient::setState(const state & s)
{
   pState = s;
}
void Patient::setHour(const int & h)
{
    if(h>=0 && h<24)
    {
        patientData.t.hour = h;
    }
}
void Patient::setMinute(const int & minut)
{
    if(minut>=0 && minut<60)
    {
        patientData.t.minute = minut;
    }
}
void Patient::setSecond(const int & sec)
{
    if(sec>=0 && sec<60)
    {
        patientData.t.second = sec;
    }
}
void Patient::setHigh(const int & h)
{
    patientData.bp.high = h;
}
void Patient::setLow(const int & l)
{
    patientData.bp.low = l;
}
void Patient::setHeartRate(const unsigned int & hrtRate )
{
    patientData.heartRate = hrtRate;
}
string Patient::getName()const
{
    return name;
}
long int Patient::getId()const
{
    return id;
}
unsigned int Patient::getAge()const
{
    return age;
}
char Patient::getGender()const
{
    return gender;
}
string Patient::getBlood()const
{
    return blood;
}
Time Patient::getTime( )const
{
    return patientData.t;
}
bloodPressure Patient::getBloodPressure()const
{
    return patientData.bp;
}
unsigned int Patient::getHeartRate()const
{
    return patientData.heartRate;
}
infoMed Patient::getInfoMed()const
{
    return patientData;
}
state Patient::getState()const
{
    return pState;
}
const vector<infoMed> Patient::getHistory()const
{
    return history;
}

void Patient::printHistory()const
{
    for(auto i= history.begin();i!=history.end();i++)
    {
        infoMed info = *i;
        cout<<info.bp.high<<"/"<<info.bp.low<<"\t"<<info.heartRate<<"\t"<<info.t.hour<<":"<<info.t.minute<<":"<<info.t.second<<"\n";
    }
}
bool Patient::operator ==(const Patient& p)const
{
    return (id == p.id);
}
bool Patient::operator !=(const Patient& p)const
{
    return !(*this == p);
}
ostream& operator <<( ostream& output , const  Patient& p)
{
    output<<"\n*** Patient info :\n";
    output<<"\n   Time             : "<<p.patientData.t.hour<<":"<<p.patientData.t.minute<<":"<<p.patientData.t.second;
    output<<"\n   Name             : "<<p.name;
    output<<"\n   Gender           : "<<p.gender;
    output<<"\n   Age              : "<<p.age;
    output<<"\n   Blood Group      : "<<p.blood;
    output<<"\n   ID               : "<<p.id;
    output<<"\n   BloodPressure    : "<<p.patientData.bp.high<<"/"<<p.patientData.bp.low;
    output<<"\n   HeartRate        : "<<p.patientData.heartRate<<endl<<endl;
    return output;
}
