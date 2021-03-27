#include "facility.h"

#include "booking.h"
#include "vector"
#include "daytime.h"
#include "monitor.h"
#include "iostream"

using namespace std;

facility::facility(string facilityName, facilityType facilityType)
{

    name = facilityName;
    type = facilityType;
    bookings = std::vector<std::vector<booking *>>(7);
}

facility::facility(string facilityName, int fType)
{
    name = facilityName;
    type = static_cast<facilityType>(fType);
    bookings = std::vector<std::vector<booking *>>(7);
}

string facility::getName()
{
    return name;
}

facilityType facility::getType()
{
    return type;
}

bool facility::isBooking(string bookingId)
{
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < bookings[i].size(); j++)
            if (bookings[i][j]->getConfirmationId().compare(bookingId) == 0)
                return true;
    return false;
}

booking *facility::getBooking(string* bookingId)
{
    cout<<bookings.size()<<endl;
    for (int i = 0; i < 7; i++)
    {cout<<"i = "<<i<<" size : "<<bookings[i].size()<<endl;
        for (int j = 0; j < bookings[i].size(); j++)
            {
            bookings[i][j]->print();
            if (bookings[i][j]->getConfirmationId().compare(*bookingId) == 0)
                return bookings[i][j];
            }
    }
    return nullptr;
}

std::vector<booking *> facility::getBookings(daytime::day day)
{
    return bookings[day];
}

void facility::updateBookings(daytime::day day, std::vector<booking *> u_bookings)
{
    bookings.at(day) = u_bookings;
}

std::vector<std::vector<booking *>> facility::getBookings()
{
    return bookings;
}

vector<daytime::duration> facility::getAvailability(daytime::day today, string confirmationId)
{
    vector<daytime::duration> availabilities;
    std::vector<booking *> day_bookings = getBookings(today);

    daytime::time start = {0, 0}, end;
    daytime::duration b_duration;

    for (int i = 0; i < day_bookings.size(); i++)
    {
        if (confirmationId.size() == 0 || day_bookings[i]->getConfirmationId().compare(confirmationId) != 0)
        {
            b_duration = day_bookings[i]->getDuration();

            if (b_duration.startDay == today)
                end = b_duration.startTime;
            else
                end = {0, 0};

            if (end.hour != start.hour || end.minute != start.minute)
            {
                daytime::duration availability = {today, start, today, end};
                availabilities.push_back(availability);
            }

            if (b_duration.endDay == today)
                start = b_duration.endTime;
            else
                start = {23, 59};
        }
    }
    end = {23, 59};

    if (end.hour != start.hour || end.minute != start.minute)
    {
        daytime::duration availability = {today, start, today, end};
        availabilities.push_back(availability);
    }

    return availabilities;
}

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

vector<vector<daytime::duration>> facility::getAvailability(daytime::day startDay, int numOfDays)
{
    vector<vector<daytime::duration>> availabilities;
    for (int i = startDay; i < numOfDays; i++)
        availabilities.push_back(getAvailability(static_cast<daytime::day>((startDay + i) % 7)));
    return availabilities;
}

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
        for (; i < bookings[day].size(); i++){
            daytime::duration b_duration = bookings[day][i]->getDuration();
            if (b_duration.startDay == day)
                if (b_duration.startTime.hour > end.hour || (b_duration.startTime.hour == end.hour && b_duration.startTime.minute > end.minute))
                    break;
        }
        bookings[day].insert( bookings[day].begin() + i, new_booking);
        // updateBookings(day, day_bookings);

        day = static_cast<daytime::day>((day + 1) % 7);
        start = {0, 0};

    } while (day != (duration.endDay + 1) % 7);

    confirmationId = new_booking->getConfirmationId();
    cout << "added booking : " << confirmationId << endl;
    return confirmationId;
}

string facility::addBooking(string ipAddress, daytime::duration duration)
{
    cout << "Adding Booking : " << daytime::getDurationStr(duration) << endl;
    string confirmationId = string();

    if (checkBookingPossible(duration))
    {
        booking *new_booking = new booking(ipAddress, duration);
        confirmationId = addBooking(new_booking);
    }
    return confirmationId;
}

bool facility::cancelBooking(string bookingId)
{
    bool bookingCancelled = false;
    booking *booking = getBooking(&bookingId);
    daytime::day day = booking->getDuration().startDay, endDay = booking->getDuration().endDay;

    if (booking)
    {
        do
        {
            for (int j = 0; j < bookings[day].size(); j++)

                if (bookings[day][j]->getConfirmationId().compare(bookingId) == 0)

                    bookings[day].erase(bookings[day].begin() + j);

            day = static_cast<daytime::day>((day + 1) % 7);

        } while (day != (endDay + 1) % 7);
        bookingCancelled = true;
        delete booking;
    }
    return bookingCancelled;
}

bool facility::changeBooking(string ipAddress, string* bookingId, int days, int hours, int minutes)
{
    cout << "CHANGE BOOKING" << endl;
    booking *p_booking = getBooking(bookingId);

    if (p_booking)
    {
        // cout << "change Booking : " << daytime::getDurationStr(p_booking->getDuration()) << endl;
        booking *new_booking = new booking(ipAddress, *bookingId, p_booking->getDuration());
        new_booking->change(days, hours, minutes);
        cout << "change Booking from : " << daytime::getDurationStr(p_booking->getDuration()) << " to :" << daytime::getDurationStr(new_booking->getDuration()) <<endl;

        if (checkBookingPossible(new_booking->getDuration(), *bookingId))
        {
            p_booking = nullptr;
            cancelBooking(*bookingId);
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

bool facility::extendBooking(string ipAddress, string* bookingId, int days, int hours, int minutes)
{
    cout << "EXTEND BOOKING" << endl;
    booking *p_booking = getBooking(bookingId);

    if (p_booking)
    {
        // cout << "extend Booking : " << daytime::getDurationStr(p_booking->getDuration()) << endl;
        booking *new_booking = new booking(ipAddress, *bookingId, p_booking->getDuration());
        new_booking->extend(days, hours, minutes);
        cout << "change Booking from : " << daytime::getDurationStr(p_booking->getDuration()) << " to :" << daytime::getDurationStr(new_booking->getDuration()) <<endl;

        if (checkBookingPossible(new_booking->getDuration(), *bookingId))
        {
            cancelBooking(*bookingId);
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

void facility::printBookings()
{
    cout << "Facility : " << name <<  " | " << convertFacilityType(type) << endl;;
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

string convertFacilityType(facilityType ftype){
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

void facility::addMonitor(monitor monitor)
{
}
std::vector<monitor> facility::getMonitors()
{
}
bool facility::isMonitor(string ipAddress)
{
}
monitor facility::getMonitor(string ipAddress)
{
}
