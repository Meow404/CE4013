#include "facility.h"

using namespace std;

/**
 * @brief  Create facility object which will hold all bookings and related information
 * @param  facilityName: Name of the facility
 * @param  facilityType: Type of the facility
 * @retval None
 */
facility::facility(string facilityName, facilityType facilityType)
{

    name = facilityName;
    type = facilityType;
    bookings = std::vector<std::vector<booking *>>(7);
}

/**
 * @brief  Created facility object with type specified as an integer
 * @param  facilityName: Name of the facility
 * @param  fType: Type of the facility specified as an integer
 * @retval None
 */
facility::facility(string facilityName, int fType)
{
    name = facilityName;
    type = static_cast<facilityType>(fType);
    bookings = std::vector<std::vector<booking *>>(7);
}

/**
 * @brief  Return the name of the facility
 * @retval facility name
 */
string facility::getName()
{
    return name;
}

/**
 * @brief  Return type of the facility
 * @retval facility type
 */
facilityType facility::getType()
{
    return type;
}

/**
 * @brief  Check of booking exists for facility with confirmation ID brovided
 * @note  booking ID = Confirmation ID
 * @param  bookingId: confirmation ID of bookinf
 * @retval True of confirmation ID exists
 */
bool facility::isBooking(string bookingId)
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < bookings[i].size(); j++)
            if (bookings[i][j]->getConfirmationId().compare(bookingId) == 0)
                return true;
    return false;
}

/**
 * @brief  Get booking corresponding to bookingId from the facility
 * @param  *bookingId: Confirmation ID provided when booking the facility
 * @retval pointer to booking object
 */
booking *facility::getBooking(string *bookingId)
{
    cout << bookings.size() << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << "i = " << i << " size : " << bookings[i].size() << endl;
        for (int j = 0; j < bookings[i].size(); j++)
        {
            bookings[i][j]->print();
            if (bookings[i][j]->getConfirmationId().compare(*bookingId) == 0)
                return bookings[i][j];
        }
    }
    return nullptr;
}

/**
 * @brief  Returns all the bookings on a particular day for the facility
 * @param  day: day for which bookings are required
 * @retval vector of pointers for booking objects for each day
 */
std::vector<booking *> facility::getBookings(daytime::day day)
{
    return bookings[day];
}

/**
 * @brief  Updates all booking by checking if they are still valid or have passed their expiration date
 * @note   This function is to be called atthe end of each day but is not used as it is out of scope
 * @retval None
 */
void facility::updateBookings()
{

    cout << "Updating Bookings for "<< name << endl;
    daytime::day today = daytime::getDay();
    daytime::time time = daytime::getTime();
    daytime::date date = daytime::getDate();

    daytime::duration b_duration;
    daytime::date bs_date;
    daytime::date be_date;

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < bookings[i].size(); j++)
        {
            b_duration = bookings[i][j]->getDuration();
            bs_date = b_duration.startDate;
            be_date = b_duration.endDate;

            if (bs_date.year < date.year || (bs_date.year == date.year && bs_date.month < date.month) || (bs_date.year == date.year && bs_date.month == date.month && bs_date.day < date.day))
            {
                if (be_date.year < date.year || (be_date.year == date.year && be_date.month < date.month) || (be_date.year == date.year && be_date.month == date.month && be_date.day < date.day))
                {
                    cout << "[DELETION] Booking Expired" << endl;
                    bookings[i][j]->print();
                    removeBooking(bookings[i][j]);
                    j--;
                }
                else
                {
                    daytime::duration new_duration = b_duration;
                    new_duration.startDate = date;
                    new_duration.startDay = today;
                    new_duration.startTime = {0, 0};

                    bookings[i][j]->print();
                    booking *new_booking = new booking(*bookings[i][j]);

                    new_booking->updateDuration(new_duration);
                    cout << "[ALTERATION] Booking Ongoing!" << endl;
                    bookings[i][j]->print();
                    new_booking->print();

                    removeBooking(bookings[i][j]);
                    addBooking(new_booking);
                    j--;
                }
            }
        }
    }
}

/**
 * @brief  Return bookings of all days for the facility
 * @retval 2D vector containing pointers to bookings for all days
 */
std::vector<std::vector<booking *>> facility::getBookings()
{
    return bookings;
}

/**
 * @brief  Get availabile slots for booking every day
 * @param  day: day for which booking slots are required
 * @param  confirmationId: All bookings linked to this confirmation ID will not be considered
 * @retval vector of durations for empty slots
 */
vector<daytime::duration> facility::getAvailability(daytime::day day, string confirmationId)
{
    vector<daytime::duration> availabilities;
    std::vector<booking *> day_bookings = getBookings(day);
    daytime::date date = daytime::getFutureDate((day + 7 - daytime::getDay()) % 7, 0, 0);

    daytime::time start = {0, 0}, end;
    daytime::duration b_duration;

    for (int i = 0; i < day_bookings.size(); i++)
    {
        if (confirmationId.size() == 0 || day_bookings[i]->getConfirmationId().compare(confirmationId) != 0)
        {
            b_duration = day_bookings[i]->getDuration();

            if (b_duration.startDay == day)
                end = b_duration.startTime;
            else
                end = {0, 0};

            if (end.hour != start.hour || end.minute != start.minute)
            {
                daytime::duration availability = {day, start, date, day, end, date};
                availabilities.push_back(availability);
            }

            if (b_duration.endDay == day)
                start = b_duration.endTime;
            else
                start = {23, 59};
        }
    }
    end = {23, 59};

    if (end.hour != start.hour || end.minute != start.minute)
    {
        daytime::duration availability = {day, start, date, day, end, date};
        availabilities.push_back(availability);
    }

    return availabilities;
}

/**
 * @brief  Print availabilities for a particular day
 * @param  day: day for which booking slots are required
 * @param  confirmationId: All bookings linked to this confirmation ID will not be considered
 * @retval None
 */
void facility::printAvailability(daytime::day day, string confirmationId)
{
    vector<daytime::duration> availabilities = getAvailability(day, confirmationId);
    char buffer[60];
    for (int j = 0; j < availabilities.size(); j++)
    {
        daytime::duration d = availabilities[j];
        sprintf(buffer, "%2d:%2d - %2d:%2d", d.startTime.hour, d.startTime.minute, d.endTime.hour, d.endTime.minute);

        cout << daytime::convertDay(d.startDay) << " : " << buffer << endl;
    }
}

/**
 * @brief  Get availability for a continuous range of days
 * @param  startDay: day on which booking is required
 * @param  numOfDays: number of days from start day for which booking is required
 * @retval 2D vector of available durations for individual days
 */
vector<vector<daytime::duration>> facility::getAvailability(daytime::day startDay, int numOfDays)
{
    vector<vector<daytime::duration>> availabilities;
    for (int i = startDay; i < numOfDays; i++)
        availabilities.push_back(getAvailability(static_cast<daytime::day>((startDay + i) % 7)));
    return availabilities;
}

/**
 * @brief  Check if booking is possible for given duration
 * @param  duration: duration for which booking is required
 * @param  confirmationId: All bookings linked to this confirmation ID will not be considered
 * @retval True if booking is possible
 */
bool facility::checkBookingPossible(daytime::duration duration, string confirmationId)
{
    daytime::day day = duration.startDay;
    daytime::time start = duration.startTime, end;

    vector<daytime::duration> availabilities;

    do
    {
        if (day != duration.endDay)
            end = {23, 59};
        else
            end = duration.endTime;

        availabilities = getAvailability(day, confirmationId);
        int i;
        for (i = 0; i < availabilities.size(); i++)
        {
            // cout << "DURATION: " << start.hour << ":" << start.minute <<" - "<<end.hour<<":"<<end.minute<<endl;
            // cout << "AVAILABILITY: "<< availabilities[i].startTime.hour << ":" << availabilities[i].startTime.minute <<" - "<<availabilities[i].endTime.hour<<":"<<availabilities[i].endTime.minute<<endl;

            if (availabilities[i].endTime.hour > start.hour || (availabilities[i].endTime.hour == start.hour && availabilities[i].endTime.minute > start.minute))
                if ((availabilities[i].startTime.hour > start.hour || (availabilities[i].startTime.hour == start.hour && availabilities[i].startTime.minute > start.minute)) || (availabilities[i].endTime.hour < end.hour || (availabilities[i].endTime.hour == end.hour && availabilities[i].endTime.minute < end.minute)))
                    return false;
                else
                    break;
        }

        if (i == availabilities.size())
            return false;

        day = static_cast<daytime::day>((day + 1) % 7);
        start = {0, 0};

    } while (day != (duration.endDay + 1) % 7);
    cout << "Booking Possible" << endl;
    return true;
}

/**
 * @brief  Additition of new booking object to facility
 * @param  *new_booking: pointer to booking object
 * @retval confirmation ID of booking
 */
string facility::addBooking(booking *new_booking)
{
    string confirmationId = string();
    std::vector<booking *> day_bookings;

    daytime::duration duration = new_booking->getDuration();
    daytime::day day = duration.startDay;
    daytime::time start = duration.startTime, end;

    do
    {
        if (day != duration.endDay)
            end = {23, 59};
        else
            end = duration.endTime;

        // day_bookings = getBookings(day);
        int i = 0;
        for (; i < bookings[day].size(); i++)
        {
            daytime::duration b_duration = bookings[day][i]->getDuration();
            if (b_duration.startDay == day)
                if (b_duration.startTime.hour > end.hour || (b_duration.startTime.hour == end.hour && b_duration.startTime.minute >= end.minute))
                    break;
        }
        cout << "Adding booking @ " << i << endl;
        bookings[day].insert(bookings[day].begin() + i, new_booking);
        // updateBookings(day, day_bookings);

        day = static_cast<daytime::day>((day + 1) % 7);
        start = {0, 0};

    } while (day != (duration.endDay + 1) % 7);

    confirmationId = new_booking->getConfirmationId();
    cout << "added booking : " << confirmationId << endl;
    return confirmationId;
}

/**
 * @brief  Add booking to facility
 * @note   Use client ID and duration to first create a booking obejct before adding it
 * @param  clientId: Unique ID for each client
 * @param  duration: duration of booking
 * @retval confirmation ID linked to booking
 */
string facility::addBooking(string clientId, daytime::duration duration)
{
    cout << "Adding Booking : " << daytime::getDurationStr(duration) << endl;
    string confirmationId = string();

    if (checkBookingPossible(duration))
    {
        booking *new_booking = new booking(clientId, duration);
        confirmationId = addBooking(new_booking);
    }
    return confirmationId;
}

/**
 * @brief  Remove booking from facility
 * @param  *booking: pointer to booking
 * @retval None
 */
void facility::removeBooking(booking *booking)
{
    daytime::day day = booking->getDuration().startDay, endDay = booking->getDuration().endDay;
    string bookingId = booking->getConfirmationId();

    do
    {
        for (int j = 0; j < bookings[day].size(); j++)
            if (bookings[day][j]->getConfirmationId().compare(bookingId) == 0)
            {
                bookings[day].erase(bookings[day].begin() + j);
                break;
            }

        day = static_cast<daytime::day>((day + 1) % 7);

    } while (day != (endDay + 1) % 7);
    delete booking;
}

/**
 * @brief  Cancel a booking
 * @note   Removes a booking if it is valid
 * @param  bookingId: confirmation ID linked to each booking
 * @retval true of cancellation is successful
 */
bool facility::cancelBooking(string bookingId)
{
    bool bookingCancelled = false;
    booking *booking = getBooking(&bookingId);
    if (booking)
    {
        removeBooking(booking);
        return true;
    }
    return false;
}

/**
 * @brief  Change booking be given number of days, hour & minutes 
 * @param  clientId: Unique ID for each client
 * @param  bookingId: Confirmation ID linked to each booking
 * @param  days: days by which booking is to offset
 * @param  hours: hours by which booking is to be offset
 * @param  minutes: minutes by which booking is to be offset
 * @retval true if booking is sucessfully changed
 */
bool facility::changeBooking(string clientId, string* bookingId, int days, int hours, int minutes)
{
    cout << "CHANGE BOOKING" << endl;
    booking *p_booking = getBooking(bookingId);

    if (p_booking)
    {
        // cout << "change Booking : " << daytime::getDurationStr(p_booking->getDuration()) << endl;
        booking *new_booking = new booking(clientId, *bookingId, p_booking->getDuration());
        new_booking->change(days, hours, minutes);
        cout << "change Booking from : " << daytime::getDurationStr(p_booking->getDuration()) << " to :" << daytime::getDurationStr(new_booking->getDuration()) << endl;

        if (checkBookingPossible(new_booking->getDuration(), *bookingId))
        {
            // p_booking = nullptr;
            removeBooking(p_booking);
            addBooking(new_booking);
            printBookings();
            return true;
        }
        else
            return false;
    }
    else
        return false;
    return true;
}

/**
 * @brief  Extend booking period by given number of days, hours and minutes
 * @param  clientId: Unique ID of each client
 * @param  bookingId: confirmation ID linked to each booking
 * @param  days: days by which booking is to be extended
 * @param  hours: hours by which booking is to be extended
 * @param  minutes: minutes by which booking is to be extended
 * @retval true if booking is successfully extended
 */
bool facility::extendBooking(string clientId, string* bookingId, int days, int hours, int minutes)
{
    cout << "EXTEND BOOKING" << endl;
    booking *p_booking = getBooking(bookingId);

    if (p_booking)
    {
        // cout << "extend Booking : " << daytime::getDurationStr(p_booking->getDuration()) << endl;
        booking *new_booking = new booking(clientId, *bookingId, p_booking->getDuration());
        new_booking->extend(days, hours, minutes);
        cout << "change Booking from : " << daytime::getDurationStr(p_booking->getDuration()) << " to :" << daytime::getDurationStr(new_booking->getDuration()) << endl;

        if (checkBookingPossible(new_booking->getDuration(), *bookingId))
        {
            removeBooking(p_booking);
            addBooking(new_booking);
            printBookings();
            return true;
        }
        else
            return false;
    }
    else
        return false;
    return true;
}

/**
 * @brief  Print all booking of the facility
 * @retval None
 */
void facility::printBookings()
{
    cout << "Facility : " << name << " | " << convertFacilityType(type) << endl;
    char buffer[40];

    for (int i = 0; i < 7; i++)
    {
        daytime::day day = static_cast<daytime::day>(i);
        cout << daytime::convertDay(day) << endl;
        for (int j = 0; j < bookings[i].size(); j++)
        {
            bookings[i][j]->print();
        }
    }
}

/**
 * @brief  Convert facility type to a string
 * @param  ftype: facilityType object
 * @retval string stating type of facility
 */
string convertFacilityType(facilityType ftype)
{
    switch (ftype)
    {
    case facilityType::LECTURE_THEATRE:
        return "Lecture Theatre";
    case facilityType::TUTORIAL_ROOM:
        return "Tutorial Room";
    case facilityType::MEETING_ROOM:
        return "Meeting Room";
    case facilityType::SPORTS_FACILITY:
        return "Sports Facility";
    default:
        return "Invalid Day";
    }
}

/**
 * @brief  Add a monitor to the facility
 * @param reqId: Request ID for addition of monitor
 * @param  clientAddress: Socket address of monitoring client
 * @param  duration: duration of monitoring period
 * @retval None
 */
void facility::addMonitor(int reqId, sockaddr_in clientAddress, daytime::duration duration)
{
    monitor monitor(reqId, clientAddress, duration);
    monitor.print();
    monitors.push_back(monitor);
}

/**
 * @brief  Get all monitors of the facility
 * @retval vector consisting of all monitors of the facility
 */
std::vector<monitor> facility::getMonitors()
{
    updateMonitors();
    return monitors;
}

/**
 * @brief  Update list of monitors by removing any monitors that have passed expiration date
 * @retval None
 */
void facility::updateMonitors()
{
    daytime::date today = daytime::getDate();
    daytime::time time = daytime::getTime();

    for (int i = 0; i < monitors.size(); i++)
    {
        daytime::duration m_duration = monitors[i].getDuration();
        daytime::date m_exp = m_duration.endDate;

        bool remove = false;
        if (m_exp.year < today.year ||
            (m_exp.year == today.year && m_exp.month < today.month) ||
            (m_exp.year == today.year && m_exp.month == today.month && m_exp.day < today.day))
            remove = true;

        if (m_exp.day == today.day &&
            (m_duration.endTime.hour < time.hour ||
            (m_duration.endTime.hour == time.hour && m_duration.endTime.minute < time.minute)))
            // Same day, curr hr > expiry hr or (curr hr = expiry hr, curr min > expiry min)
            remove = true;

        if (remove)
        {
            cout << "Removing monitor : " << monitors[i].getIpAddress() << " for facility '" << name << "' as monitoring period has expired!" << endl;
            monitors.erase(monitors.begin() + i);
            i--;
        }
    }
}

/**
 * @brief  Check if IP Address is a monitor of the facility 
 * @param  ipAddress: address of monitor 
 * @retval true of ipAddress is a monitor
 */
bool facility::isMonitor(string ipAddress)
{
    updateMonitors();
    for (int i = 0; i < monitors.size(); i++)
        if (monitors[i].getIpAddress().compare(ipAddress) == 0)
            return true;
    return false;
}

/**
 * @brief  Get monitor based on ipAddress
 * @param  ipAddress: Ipaddress of monitor required
 * @retval monitor object
 */
monitor facility::getMonitor(string ipAddress)
{
    updateMonitors();
    for (int i = 0; i < monitors.size(); i++)
        if (monitors[i].getIpAddress().compare(ipAddress) == 0)
            return monitors[i];
}
