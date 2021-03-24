#ifndef BOOKING
#define BOOKING

#include "daytime.h"

class booking
{
    daytime::duration duration;
    char* bookingId;

    public:
    booking(daytime::duration duration);
    char* getBookingId();
    void change(int days, int hours, int minutes);
    void extend(int days, int hours, int minutes);
};

#endif