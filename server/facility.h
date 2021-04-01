#ifndef FACILITY
#define FACILITY

#include "booking.h"
#include "vector"
#include "daytime.h"
#include "monitor.h"
#include "string"
#include "iostream"

/**
 * @brief  facility types stored as an emuerated
 */
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
    void removeBooking(booking* booking);
    std::string getFacilityType(facilityType ftype);
    bool checkChange(daytime::duration duration, int days, int hours, int minutes);

public:
    facility(std::string facilityName, facilityType facilityType);
    facility(std::string facilityName, int fType);
    std::string getName();
    facilityType getType();

    bool isBooking(std::string bookingId);
    booking* getBooking(std::string* bookingId);
    void updateBookings();
    bool cancelBooking(std::string bookingId);
    

    std::vector<booking*> getBookings(daytime::day day);
    std::vector<std::vector<booking*>> getBookings();

    std::vector<daytime::duration> getAvailability(daytime::day day, std::string confirmationId = std::string());
    void printAvailability(daytime::day day, std::string confirmationId = std::string());
    std::vector<std::vector<daytime::duration>> getAvailability(daytime::day startDay, int numOfDays);

    bool checkBookingPossible(daytime::duration duration, std::string confirmationId = std::string());
    std::string addBooking(std::string ipAddress, daytime::duration duration);
    int changeBooking(std::string ipAddress, std::string* bookingId, int days, int hours, int minutes);
    int extendBooking(std::string ipAddress, std::string* bookingId, int days, int hours, int minutes);
    void printBookings();

    void addMonitor(int reqId, sockaddr_in clientAddress, daytime::duration duration);
    std::vector<monitor> getMonitors();
    void updateMonitors();
    bool isMonitor(std::string ipAddress);
    monitor getMonitor(std::string ipAddress);
};

#endif