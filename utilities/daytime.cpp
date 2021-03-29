#include "daytime.h"

daytime::day daytime::getDay(int dayNum)
{
    if (dayNum == 0) {
        return daytime::day::MONDAY;
    } else if (dayNum == 1) {
        return daytime::day::TUESDAY;
    } else if (dayNum == 2) {
        return daytime::day::WEDNESDAY;
    } else if (dayNum == 3) {
        return daytime::day::THURSDAY;
    } else if (dayNum == 4) {
        return daytime::day::FRIDAY;
    } else if (dayNum == 5) {
        return daytime::day::SATURDAY;
    } else if (dayNum == 6) {
        return daytime::day::SUNDAY;
    }
    return daytime::day::INVALID;
}

std::string daytime::getDayStr(int dayNum) {
    if (dayNum == daytime::day::MONDAY) {
        return "MON";
    } else if (dayNum == daytime::day::TUESDAY) {
        return "TUES";
    } else if (dayNum == daytime::day::WEDNESDAY) {
        return "WED";
    } else if (dayNum == daytime::day::THURSDAY) {
        return "THURS";
    } else if (dayNum == daytime::day::FRIDAY) {
        return "FRI";
    } else if (dayNum == daytime::day::SATURDAY) {
        return "SAT";
    } else if (dayNum == daytime::day::SUNDAY) {
        return "SUN";
    }
    return "INVALID DAY";
}
