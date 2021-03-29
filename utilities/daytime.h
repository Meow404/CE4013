#ifndef DAYTIME
#define DAYTIME

#include <string>

namespace daytime
{
    enum day
    {

        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,        
        SUNDAY,
        INVALID
    };

    struct time{
        int hour;
        int minute;
    };

    struct duration{
        day startDay;
        time startTime;
        day endDay;
        time endTime;
    };

    day getDay(int dayNum);
    std::string getDayStr(int dayNum);
}

#endif