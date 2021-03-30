#include "daytime.h"
#include "string"

using namespace std::chrono;

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
    char buffer[50];
    sprintf(buffer, "%s %02d:%02d - %s %02d:%02d", convertDay(duration.startDay).c_str(),duration.startTime.hour, duration.startTime.minute, convertDay(duration.endDay).c_str(),duration.endTime.hour, duration.endTime.minute );
    return (std::string) buffer;
}

daytime::time daytime::getTime(){
    time_t now = system_clock::to_time_t(system_clock::now());
    tm *ltm = localtime(&now);

    daytime::time time;
    time.hour = ltm->tm_hour;
    time.minute = ltm->tm_min;
    return time;
}
daytime::day daytime::getDay(){
    time_t now = system_clock::to_time_t(system_clock::now());
    tm *ltm = localtime(&now);
    daytime::day day;
    day = static_cast<daytime::day>((ltm->tm_wday+6)%7);
    return day;
}

daytime::date daytime::getDate(){
    time_t now = system_clock::to_time_t(system_clock::now());
    tm *ltm = localtime(&now);

    daytime::date date;
    date.day = ltm->tm_mday;
    date.month = ltm->tm_mon + 1;
    date.year = ltm->tm_year + 1900;
    return date;
}

daytime::date daytime::getFutureDate(int days, int hours, int minutes){
    system_clock::time_point t = std::chrono::system_clock::now();
    system_clock::time_point new_t = t + std::chrono::minutes(days*24*60 + hours*24 + minutes);

    time_t now = system_clock::to_time_t(new_t);
    tm *ltm = localtime(&now);

    daytime::date date;
    date.day = ltm->tm_mday;
    date.month = ltm->tm_mon + 1;
    date.year = ltm->tm_year + 1900;
    return date;
}