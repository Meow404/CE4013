#include "daytime.h"
#include "string"

std::string daytime::convertDay(day day)
{
    switch (day)
    {
    case day::MONDAY:
        return "Monday";
    case day::TUEDAY:
        return "Tuesday";
    case day::WEDNESDAY:
        return "Wednesday";
    case day::THURSDAY:
        return "Thursday";
    case day::FRIDAY:
        return "Friday";
    case day::SATURDAY:
        return "Saturday";
    case day::SUNDAY:
        return "Sunday";
    default:
        return "Invalid Day";
    }
}

std::string daytime::getDurationStr(daytime::duration duration){
    char buffer[20];
    sprintf(buffer, "%s %02d:%02d - %s %02d:%02d", convertDay(duration.startDay).c_str(),duration.startTime.hour, duration.startTime.minute, convertDay(duration.endDay).c_str(),duration.endTime.hour, duration.endTime.minute );
    return (std::string) buffer;
}