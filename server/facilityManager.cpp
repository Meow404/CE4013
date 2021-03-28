#include "facilityManager.h"
#include "string"
#include "facility.h"
#include "daytime.h"
#include "iostream"

using namespace std;

bool facilityManager::checkDuration(int s_day, int s_hour, int s_minute, int e_day, int e_hour, int e_minute)
{
    if (!checkDayTime(s_day, s_hour, s_minute) || !checkDayTime(e_day, e_hour, e_minute))
        return false;
    if (s_day == e_day && s_hour > e_hour)
        return false;
    if (s_day == e_day && s_hour == e_hour && s_minute > e_minute)
        return false;
    return true;
}
bool facilityManager::checkDayTime(int day, int hour, int minute)
{
    if (day >= 7)
        return false;
    if (hour >= 24)
        return false;
    if (minute >= 60)
        return false;
    return true;
}

facilityManager::facilityManager(const char *filename)
{
    std::ifstream file(filename);
    std::string str, split, facilityName;
    int numOfFacilities, facilityType;
    vector<string> results;

    std::getline(file, str);
    numOfFacilities = stoi(str);

    for (int i = 0; i < numOfFacilities; i++)
    {
        std::getline(file, str);
        stringstream ss(str);
        std::getline(ss, split, ',');
        facilityType = stoi(split);
        std::getline(ss, split, ',');
        facilityName = split;
        addFacility(facilityName, facilityType);
    }
}

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

std::vector<daytime::duration> facilityManager::getFacilityAvailability(string facilityName, int day)
{
    facility *facility = getFacility(facilityName);
    if (day < 7)
    {
        daytime::day day = static_cast<daytime::day>(day);
        cout << "Sending Bookings of " << daytime::convertDay(day);
        return facility->getAvailability(day);
    }
    else
        return {};
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

int facilityManager::addFacilityBooking(std::string ipAddress, std::string *confirmationId, string facilityName, int s_day, int s_hour, int s_minute, int e_day, int e_hour, int e_minute)
{
    cout << facilityName << endl;
    facility *facility = getFacility(facilityName);
    if (!facility)
        return 1;

    if (!checkDuration(s_day, s_hour, s_minute, e_day, e_hour, e_minute))
        return 3;
    daytime::duration duration;
    duration.startDay = static_cast<daytime::day>(s_day);
    duration.startTime = {s_hour, s_minute};
    duration.endDay = static_cast<daytime::day>(e_day);
    duration.endTime = {e_hour, e_minute};
    *confirmationId = facility->addBooking(ipAddress, duration);
    if (confirmationId->size() == 0)
        return 2;
    else
        return 0;
}

int facilityManager::changeFacilityBooking(std::string ipAddress, string *confirmationId, int days, int hours, int minutes)
{
    facility *facility = getBookingFacility(*confirmationId);

    if (!facility)
        return 1;

    if (!checkDayTime(days, hours, minutes))
        return 3;

    if (!facility->changeBooking(ipAddress, confirmationId, days, hours, minutes))
        return 2;
    else
        return 0;
}

int facilityManager::extendFacilityBooking(std::string ipAddress, string *confirmationId, int days, int hours, int minutes)
{
    facility *facility = getBookingFacility(*confirmationId);

    if (!facility)
        return 1;

    if (!checkDayTime(days, hours, minutes))
        return 3;

    if (!facility->extendBooking(ipAddress, confirmationId, days, hours, minutes))
        return 2;
    else
        return 0;
}

bool facilityManager::cancelFacilityBooking(string confirmationId)
{
    facility *facility = getBookingFacility(confirmationId);
    if (!facility)
        return false;
    facility->cancelBooking(confirmationId);
    return true;
}

void facilityManager::printFacilities()
{
    for (int i = 0; i < facilities.size(); i++)
    {
        facilities[i]->printBookings();
    }
}