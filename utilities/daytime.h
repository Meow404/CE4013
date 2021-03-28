#ifndef DAYTIME
#define DAYTIME

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
}

#endif