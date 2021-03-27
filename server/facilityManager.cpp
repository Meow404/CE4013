#include "facilityManager.h"
#include "string"
#include "facility.h"
#include "daytime.h"
#include "iostream"

using namespace std;

void facilityManager::addFacility(string facilityName, int fIndex)
{
    facilityType fType = static_cast<facilityType>(fIndex);
    facilities.push_back(new facility(facilityName, fType));
}

bool facilityManager::isFacility(std::string facilityName)
{
    for (int i = 0; i < facilities.size(); i++)
        if (facilities[i]->getName().compare(facilityName) == 0)
            return true;
    return false;
}

facility *facilityManager::getFacility(std::string facilityName)
{
    for (int i = 0; i < facilities.size(); i++)
        if (facilities[i]->getName().compare(facilityName) == 0)
            return facilities[i];
    return nullptr;
}

facility *facilityManager::getBookingFacility(std::string bookingId)
{
    for (int i = 0; i < facilities.size(); i++)
        if (facilities[i]->isBooking(bookingId))
            return facilities[i];
    return nullptr;
}

std::vector<std::vector<daytime::duration>> facilityManager::getFacilityAvailability(string facilityName, vector<int> days)
{
    std::vector<std::vector<daytime::duration>> availabilities;
    facility *facility = getFacility(facilityName);
    for (int i = 0; i < days.size(); i++)
    {
        daytime::day day = static_cast<daytime::day>(days[i]);
        availabilities.push_back(facility->getAvailability(day));
    }
    return availabilities;
}

void facilityManager::addMonitorForFacility(string facilityName, string ipAddress, int port, int day, int hours, int minutes)
{
}
void facilityManager::extendMonitorForFacility(string facilityName, string ipAddress, int port, int day, int hours, int minutes)
{
}

string facilityManager::addFacilityBooking(std::string ipAddress, string facilityName, int s_day, int s_hour, int s_minute, int e_day, int e_hour, int e_minute)
{
    facility *facility = getFacility(facilityName);
    daytime::duration duration;
    duration.startDay = static_cast<daytime::day>(s_day);
    duration.startTime = {s_hour, s_minute};
    duration.endDay = static_cast<daytime::day>(e_day);
    duration.endTime = {e_hour, e_minute};
    return facility->addBooking(ipAddress, duration);
}

bool facilityManager::changeFacilityBooking(std::string ipAddress, string *confirmationId, int days, int hours, int minutes)
{
    facility *facility = getBookingFacility(*confirmationId);
    return facility->changeBooking(ipAddress, confirmationId, days, hours, minutes);
}

bool facilityManager::extendFacilityBooking(std::string ipAddress, string *confirmationId, int days, int hours, int minutes)
{
    facility *facility = getBookingFacility(*confirmationId);
    return facility->extendBooking(ipAddress, confirmationId, days, hours, minutes);
}

bool facilityManager::cancelFacilityBooking(string confirmationId)
{
    facility *facility = getBookingFacility(confirmationId);
    return facility->cancelBooking(confirmationId);
}

void facilityManager::printFacilities()
{
    for (int i = 0; i < facilities.size(); i++)
    {
        facilities[i]->printBookings();
    }
}