#include "booking.h"
#include "daytime.h"
#include "facility.h"
#include "iostream"
#include "facilityManager.h"
#include <fstream>
#include <sstream>
#include "vector"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    std::ifstream file("facilities.txt");
    std::string str, split, facilityName;
    int fnum, facilityType;
    facilityManager FM;
    vector<string> results;

    std::getline(file, str);
    fnum = stoi(str);

    for(int i = 0; i<fnum; i++){
        std::getline(file, str);
        stringstream  ss(str);
        std::getline(ss, split, ',');
        facilityType = stoi(split);
        std::getline(ss, split, ',');
        facilityName = split;
        FM.addFacility(facilityName, facilityType);
    }

    FM.printFacilities();
    srand (time(NULL));
    vector<string> cids;

    for (int i = 0; i < 50; i++){
        cout << "i : "<<i<<endl;
        int start_day = rand()%7;
        int start_hour = rand()%24;
        int start_minute = rand()%60;
        int end_day = (start_day + rand()%2)%7;
        int end_hour = start_day == end_day? start_hour + rand()%(24-start_hour) : rand()%24;
        int end_minute = start_hour == end_hour? start_minute + rand()%(60-start_minute) : rand()%60;
        string cid = FM.addFacilityBooking("192.168.1.45", "Lecture Theatre 1", start_day, start_hour, start_minute, end_day, end_hour, end_minute);
        for (int j=0; j<1000000000; j++){}

        if(cid.size() != 0)
            cids.push_back(cid);
        
        if (cids.size()!=0){
            
        start_day = rand()%2;
        start_hour = rand()%24;
        start_minute = rand()%60;
        cid = cids[rand()%cids.size()];
        FM.changeFacilityBooking("192.168.1.45", &cid, start_day, start_hour, start_minute);
        for (int j=0; j<1000000000; j++);

        start_day = rand()%2;
        start_hour = rand()%24;
        start_minute = rand()%60;
        cid = cids[rand()%cids.size()];
        FM.extendFacilityBooking("192.168.1.45", &cid,  start_day, start_hour, start_minute);
        for (int j=0; j<1000000000; j++);
        FM.printFacilities();
        }
    }
    // FM.printFacilities();
    // string cid2 = FM.addFacilityBooking("192.168.1.45", "Lecture Theatre 2", 1, 2, 30, 2, 3, 30);
    // FM.printFacilities();
    // FM.getFacility("Lecture Theatre 2")->printAvailability(daytime::TUEDAY);
    // string cid3 = FM.addFacilityBooking("192.168.1.45", "Lecture Theatre 2", 1, 3, 30, 2, 3, 30);
    // FM.printFacilities();
}