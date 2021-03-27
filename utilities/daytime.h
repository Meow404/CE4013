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

    day getDay(int dayNum)
    {
        if (dayNum == 0) {
            return MONDAY;
        } else if (dayNum == 1) {
            return TUESDAY;
        } else if (dayNum == 2) {
            return WEDNESDAY;
        } else if (dayNum == 3) {
            return THURSDAY;
        } else if (dayNum == 4) {
            return FRIDAY;
        } else if (dayNum == 5) {
            return SATURDAY;
        } else if (dayNum == 6) {
            return SUNDAY;
        }
    }
}

#endif