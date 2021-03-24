#ifndef FACILITY
#define FACILITY

#include "booking.h"
#include "vector"
#include "daytime.h"
#include "monitor.h"

namespace facility
{

    enum facilityType{
        LECTURE_THEATRE,
        TUTORIAL_ROOM,
        MEETING_ROOM,
        SPORTS_FACILITY
    };

    class facility
    {
        char *name;
        facilityType type;
        std::vector<std::vector<booking>> bookings;
        std::vector<monitor> monitors;

        public:

        char* getName();
        facilityType getType();

        bool isBooking(char* bookingId);
        booking getBooking(char* bookingId);
        void cancelBooking(char* bookingId);

        std::vector<booking> getBookings(daytime::day day);
        std::vector<std::vector<booking>> getBookings();

        std::vector<daytime::duration> getAvailability(daytime::day day);
        std::vector<std::vector<daytime::duration>> getAvailability(daytime::day startDay, daytime::day endDay);

        void addBooking(daytime::duration duration);
        void changeBooking(char* bookingId, int days, int hours, int minutes);
        void extendBooking(char* bookingId, int days, int hours, int minutes);

        void addMonitor(monitor monitor);
        std::vector<monitor> getMonitors();
        bool isMonitor(char* ipAddress);
        monitor getMonitor(char* ipAddress);
    };

}

#endif FACILITY