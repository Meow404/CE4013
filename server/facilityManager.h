#ifndef FACILITYMANAGER
#define FACILITYMANAGER

#include "facility.h"
#include "booking.h"
#include "vector"
#include "string"
#include "daytime.h"
#include "monitor.h"
#include <fstream>
#include <sstream>
#include "vector"
#include <stdlib.h>

class facilityManager
{
    std::vector<facility *> facilities;

    bool checkDuration(int s_day, int s_hour, int s_minute, int e_day, int e_hour, int e_minute);
    bool checkDayTime(int day, int hour, int minute);

public:
    facilityManager(const char* filename);
    void addFacility(std::string facilityName, int facilityType);
    bool isFacility(std::string facilityName);
    void printFacilities();
    facility *getFacility(std::string facilityName);
    facility *getBookingFacility(std::string bookingId);
    std::vector<daytime::duration> getFacilityAvailability(facility* facility, int day);
    std::vector<std::vector<daytime::duration>> getFacilityAvailability(facility* facility, std::vector<int> days);

    int addMonitorForFacility(facility* facility, struct sockaddr_in clientAddress, int day, int hours, int minutes);
    int extendMonitorForFacility(facility* facility, std::string ipAddress, int day, int hours, int minutes);

    int addFacilityBooking(std::string ipAddress, std::string* confirmationId, facility* facility, int s_day, int s_hour, int s_minute, int e_day, int e_hour, int e_minute);
    int changeFacilityBooking(std::string ipAddress, std::string* confirmationId, facility* facility, int day, int hours, int minutes);
    int extendFacilityBooking(std::string ipAddress, std::string* confirmationId, facility* facility, int day, int hours, int minutes);
    bool cancelFacilityBooking(std::string confirmationId, facility* facility);
    void updateAllFacilityBookings();
    std::vector<std::string> getFacilityNames();
};

#endif