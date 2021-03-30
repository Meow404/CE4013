#include "booking.h"
#include "daytime.h"
#include "facility.h"
#include "iostream"
#include "facilityManager.h"
#include "udpServer.h"
#include "commHandler.h"
#include <fstream>
#include <sstream>
#include "vector"
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    facilityManager FM("facilities.txt");
    udpServer server(8080, AT_MOST_ONCE);
    commHandler cm(&server, &FM);
    cm.start();

    // facility* f = FM.getFacility("Lecture Theatre 1");
    // string cid1, cid2, cid3;
    // FM.addFacilityBooking("192.168.1.46", &cid1, f, 1, 2, 30, 2, 3, 30);
    // FM.addFacilityBooking("192.168.1.47", &cid2, f, 2, 3, 30, 3, 2, 30);
    // FM.addFacilityBooking("192.168.1.48", &cid3, f, 3, 2, 30, 4, 3, 30);
    // f->printAvailability(daytime::TUEDAY);
    // f->printAvailability(daytime::WEDNESDAY);
    // f->printAvailability(daytime::THURSDAY);
    // f->printAvailability(daytime::FRIDAY);
    // f->printBookings();
    // FM.cancelFacilityBooking(cid1, f);
    // f->printBookings();
}