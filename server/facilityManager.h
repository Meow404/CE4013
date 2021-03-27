#ifndef FACILITYMANAGER
#define FACILITYMANAGER

#include "facility.h"
#include "booking.h"
#include "vector"
#include "string"

class facilityManager{
    std::vector<facility*> facilities;

    public:
    void addFacility(std::string facilityName, int facilityType);
    bool isFacility(std::string facilityName);
    void printFacilities();
    facility* getFacility(std::string facilityName);
    facility* getBookingFacility(std::string bookingId);
    std::vector<std::vector<daytime::duration>> getFacilityAvailability(std::string facilityName, std::vector<int> days);

    void addMonitorForFacility(std::string facilityName, std::string ipAddress, int port, int day, int hours, int minutes);
    void extendMonitorForFacility(std::string facilityName, std::string ipAddress, int port, int day, int hours, int minutes);

    std::string addFacilityBooking(std::string ipAddress, std::string facilityName, int s_day, int s_hour, int s_minute, int e_day, int e_hour, int e_minute);
    bool changeFacilityBooking(std::string ipAddress, std::string *confirmationId, int day, int hours, int minutes);
    bool extendFacilityBooking(std::string ipAddress, std::string *confirmationId, int day, int hours, int minutes);
    bool cancelFacilityBooking(std::string confirmationId);
};

#endif