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