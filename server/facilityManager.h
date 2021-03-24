#ifndef FACILITYMANAGER
#define FACILITYMANAGER

#include "facility.h"
#include "vector"

class facilityManager{
    std::vector<facility::facility> facilities;
    public:
    void addFacility(char* facilityName, int facilityType);
    void getFacilityAvailability(char* facilityName, std::vector<int> days);

    void addMonitorForFacility(char* facilityName, char* ipAddress, int port, int day, int hours, int minutes);
    void extendMonitorForFacility(char* facilityName, char* ipAddress, int port, int day, int hours, int minutes);

    void addFacilityBooking(char* facilityName, int s_day, int s_hour, int s_minute, int e_day, int e_hour, int e_minute);
    void changeFacilityBooking(char* confirmationId, int day, int hours, int minutes);
    void extendFacilityBooking(char* confirmationId, int day, int hours, int minutes);
    void cancelFacilityBooking(char* confirmationId);
};

#endif