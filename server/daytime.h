#ifndef DAYTIME
#define DAYTIME

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
}

#endif