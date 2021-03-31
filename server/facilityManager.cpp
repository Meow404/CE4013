#include "facilityManager.h"
#include "iostream"

using namespace std;

/**
 * @brief  Check if duration provided is within bounds
 * @param  s_day: start day
 * @param  s_hour: start hour
 * @param  s_minute: start minute
 * @param  e_day: end day
 * @param  e_hour: end hour
 * @param  e_minute: end minute
 * @retval true if duration is within bounds
 */
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

/**
 * @brief  Check if values are within bounds
 * @param  day: day of the week (0-6)
 * @param  hour: hour of the day (0-23)
 * @param  minute: minute of the hour (0-59)
 * @retval true if time values are within bounds
 */
bool facilityManager::checkDayTime(int day, int hour, int minute)
{
    if (day >= 7 && day < 0)
        return false;
    if (hour >= 24 && hour < 0)
        return false;
    if (minute >= 60 && hour < 0)
        return false;
    return true;
}

/**
 * @brief  Facility manager constructor with use of a file containing list of facilities
 * @param  *filename: name of file storing facilities
 * @retval None
 */
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

/**
 * @brief  Add facility to the list of facilities managed by facility manager
 * @param  facilityName: name of facility to be added
 * @param  fIndex: type of facility to be added
 * @retval None
 */
void facilityManager::addFacility(string facilityName, int fIndex)
{
    facilityType fType = static_cast<facilityType>(fIndex);
    facilities.push_back(new facility(facilityName, fType));
}

/**
 * @brief  Check if provided facility name is a valid facility
 * @param  facilityName: name of facility
 * @retval true of facility exists
 */
bool facilityManager::isFacility(std::string facilityName)
{
    for (int i = 0; i < facilities.size(); i++)
        if (facilities[i]->getName().compare(facilityName) == 0)
            return true;
    return false;
}

/**
 * @brief  Get facility object based on facility name
 * @param  facilityName: name of facility
 * @retval pointer to facility object
 */
facility *facilityManager::getFacility(std::string facilityName)
{
    for (int i = 0; i < facilities.size(); i++)
        if (facilities[i]->getName().compare(facilityName) == 0)
            return facilities[i];
    return nullptr;
}

/**
 * @brief  Get facility object based on whether it contains a confirmation ID
 * @param  bookingId: Confirmation ID provided to each booking
 * @retval pointer to facility object
 */
facility *facilityManager::getBookingFacility(std::string bookingId)
{
    for (int i = 0; i < facilities.size(); i++)
        if (facilities[i]->isBooking(bookingId))
            return facilities[i];
    return nullptr;
}

/**
 * @brief  get availabilities of a facility for a particular day
 * @note   Pointers to facility are used for reusability
 * @param  facility: pointer to facility object from which availability is required
 * @param  day: day on which availablities are required
 * @retval vector of available durations
 */
std::vector<daytime::duration> facilityManager::getFacilityAvailability(facility *facility, int day)
{
    if (facility && day < 7)
    {
        daytime::day b_day = static_cast<daytime::day>((int)day);
        cout << "Sending Bookings of " << daytime::convertDay(b_day) << endl;
        return facility->getAvailability(b_day);
    }
    else
        return {};
}

/**
 * @brief  Get availabilities of multiple days
 * @param  facility: pointer to facility for which bookings are required
 * @param  days: vector of days for which durations are required
 * @retval 2D vector of availabilities 
 */
std::vector<std::vector<daytime::duration>> facilityManager::getFacilityAvailability(facility *facility, vector<int> days)
{
    std::vector<std::vector<daytime::duration>> availabilities;
    for (int i = 0; i < days.size(); i++)
    {
        daytime::day day = static_cast<daytime::day>(days[i]);
        availabilities.push_back(facility->getAvailability(day));
    }
    return availabilities;
}

/**
 * @brief  Add a monitor for a particular facility
 * @param  facility: facility for which monitor is to be added
 * @param  clientAddress: socked adderss of client
 * @param  day: number of days for monitoring
 * @param  hours: number of hours for monitoring
 * @param  minutes: number of minuted for monitoring
 * @retval 0 if all requirements are met
 */
int facilityManager::addMonitorForFacility(facility *facility, struct sockaddr_in clientAddress, int day, int hours, int minutes)
{
    if (!facility)
        return 1;

    if (!checkDayTime(day, hours, minutes))
        return 2;

    daytime::duration duration;

    duration.startDay = daytime::getDay();
    duration.startTime = daytime::getTime();
    duration.startDate = daytime::getDate();

    duration.endTime.minute = duration.startTime.minute + minutes;
    duration.endTime.hour = duration.startTime.hour + hours + duration.endTime.minute / 60;
    duration.endDay = static_cast<daytime::day>((duration.startDay + day + duration.endTime.hour / 24) % 7);
    duration.endTime.minute %= 60;
    duration.endTime.hour %= 24;
    duration.endDate = daytime::getFutureDate(day, hours, minutes);

    facility->addMonitor(clientAddress, duration);

    return 0;
}

/**
 * @brief  Extend monitoring period of a facility
 * @note   Not implemented (out of scope)
 * @param  facility: pointer to facility for which monitoring period is to be extended 
 * @param  ipAddress: ipAddress of monitor
 * @param  day: additional days
 * @param  hours: additional hours
 * @param  minutes: additional minutes
 * @retval 0 if extension is successful
 */
int facilityManager::extendMonitorForFacility(facility *facility, string ipAddress, int day, int hours, int minutes)
{
}

/**
 * @brief  Add booking for a facility
 * @param  clientId: Unique ID for each client
 * @param  confirmationId: pointer to string for confirmation ID
 * @param  facility: pointer to facility for which booking is to be added 
 * @param  s_day: start day
 * @param  s_hour: start hour
 * @param  s_minute: start minute
 * @param  e_day: end day
 * @param  e_hour: end hour
 * @param  e_minute: end minute
 * @retval return 0 if successful adding of booking for facility
 */
int facilityManager::addFacilityBooking(std::string ipAddress, std::string *confirmationId, facility *facility, int s_day, int s_hour, int s_minute, int e_day, int e_hour, int e_minute)
{
    if (!facility)
        return 1;

    if (!checkDuration(s_day, s_hour, s_minute, e_day, e_hour, e_minute))
        return 3;

    daytime::duration duration;
    daytime::day today = daytime::getDay();

    duration.startDay = static_cast<daytime::day>(s_day);
    duration.startTime = {s_hour, s_minute};
    duration.startDate = daytime::getFutureDate((duration.startDay + 7 - today) % 7, 0, 0);

    duration.endDay = static_cast<daytime::day>(e_day);
    duration.endTime = {e_hour, e_minute};
    duration.endDate = daytime::getFutureDate((duration.endDay + 7 - today) % 7, 0, 0);

    *confirmationId = facility->addBooking(ipAddress, duration);
    if (confirmationId->size() == 0)
        return 2;
    else
        return 0;
}

/**
 * @brief  Change facility booking by an offset
 * @param  clientId: Unique ID for each client
 * @param  confirmationId: pointer to string for confirmation ID
 * @param  facility: pointer to facility for which booking is to be added 
 * @param  days: days by which booking is to offset
 * @param  hours: hours by which booking is to be offset
 * @param  minutes: minutes by which booking is to be offset
 * @retval 0 if booking is siccessfully changes
 */
int facilityManager::changeFacilityBooking(std::string ipAddress, string *confirmationId, facility *facility, int days, int hours, int minutes)
{
    if (!facility)
        return 1;

    if (!checkDayTime(days, hours, minutes))
        return 3;

    if (!facility->changeBooking(ipAddress, confirmationId, days, hours, minutes))
        return 2;
    else
        return 0;
}

/**
 * @brief  Extend end time of booking
 * @param  clientId: Unique ID for each client
 * @param  confirmationId: pointer to string for confirmation ID
 * @param  facility: pointer to facility for which booking is to be added 
 * @param  days: days by which booking is to extended
 * @param  hours: hours by which booking is to be extended
 * @param  minutes: minutes by which booking is to be extended
 * @retval 0 if booking is siccessfully changes
 */
int facilityManager::extendFacilityBooking(std::string ipAddress, string *confirmationId, facility *facility, int days, int hours, int minutes)
{
    if (!facility)
        return 1;

    if (!checkDayTime(days, hours, minutes))
        return 3;
    if (!facility->extendBooking(ipAddress, confirmationId, days, hours, minutes))
        return 2;
    else
        return 0;
}

/**
 * @brief  Cancel booking 
 * @param  confirmationId: pointer to string for confirmation ID
 * @param  facility: pointer to facility for which booking is to be added  
 * @retval 0 if booking is successfully cancelled
 */
int facilityManager::cancelFacilityBooking(string confirmationId, facility *facility)
{
    if (!facility)
        return 1;
    facility->cancelBooking(confirmationId);
    return 0;
}

/**
 * @brief  Print bookings of all facilities
 * @retval None
 */
void facilityManager::printFacilities()
{
    for (int i = 0; i < facilities.size(); i++)
    {
        facilities[i]->printBookings();
    }
}

/**
 * @brief  Update booking of all facilities, to be called at the start of a new day
 * @retval None
 */
void facilityManager::updateAllFacilityBookings()
{
    for (int i = 0; i < facilities.size(); i++)
    {
        facilities[i]->updateBookings();
    }
}

/**
 * @brief  Get list of facities available
 * @retval vector containing list of facilities
 */
std::vector<std::string> facilityManager::getFacilityNames()
{
    std::vector<std::string> names;
    for (int i = 0; i < facilities.size(); i++)
    {
        names.push_back(facilities[i]->getName());
    }
    return names;
}