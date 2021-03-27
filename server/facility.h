#ifndef FACILITY
#define FACILITY

#include "booking.h"
#include "vector"
#include "daytime.h"
#include "monitor.h"
#include "string"

enum facilityType
{
    LECTURE_THEATRE,
    TUTORIAL_ROOM,
    MEETING_ROOM,
    SPORTS_FACILITY
};

std::string convertFacilityType(facilityType ftype);

class facility
{
    std::string name;
    facilityType type;
    std::vector<std::vector<booking*>> bookings;
    std::vector<monitor> monitors;

    std::string addBooking(booking *new_booking);
    std::string getFacilityType(facilityType ftype);

public:
    facility(std::string facilityName, facilityType facilityType);
    facility(std::string facilityName, int fType);
    std::string getName();
    facilityType getType();

    bool isBooking(std::string bookingId);
    booking* getBooking(std::string* bookingId);
    void updateBookings(daytime::day day, std::vector<booking*> u_bookings);
    bool cancelBooking(std::string bookingId);

    std::vector<booking*> getBookings(daytime::day day);
    std::vector<std::vector<booking*>> getBookings();

    std::vector<daytime::duration> getAvailability(daytime::day day, std::string confirmationId = std::string());
    void printAvailability(daytime::day day, std::string confirmationId = std::string());
    std::vector<std::vector<daytime::duration>> getAvailability(daytime::day startDay, int numOfDays);

    bool checkBookingPossible(daytime::duration duration, std::string confirmationId = std::string());
    std::string addBooking(std::string ipAddress, daytime::duration duration);
    bool changeBooking(std::string ipAddress, std::string* bookingId, int days, int hours, int minutes);
    bool extendBooking(std::string ipAddress, std::string* bookingId, int days, int hours, int minutes);
    void printBookings();

    void addMonitor(monitor monitor);
    std::vector<monitor> getMonitors();
    bool isMonitor(std::string ipAddress);
    monitor getMonitor(std::string ipAddress);
};

#endif