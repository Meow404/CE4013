#ifndef DAYTIME
#define DAYTIME

#include "string"
#include "chrono"

namespace daytime
{
    enum day
    {

        MONDAY,
        TUEDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };

    std::string convertDay(day day);

    struct date
    {
        int day;
        int month;
        int year;
    };

    struct time
    {
        int hour;
        int minute;
    };

    struct duration
    {
        day startDay;
        time startTime;
        day endDay;
        time endTime;
    };

    std::string getDurationStr(duration duration);
    time getTime();
    day getDay();
    date getDate();
    date getFutureDate(int days, int hours, int minutes);
}

#endif