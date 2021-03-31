#include "daytime.h"
#include "string"

using namespace std::chrono;

/**
 * @brief  Convert day from enum to string
 * @param  day: day of enum type
 * @retval string of day
 */
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

/**
 * @brief  Get string interpretation for the duration
 * @param  duration: duration
 * @retval string representation
 */
std::string daytime::getDurationStr(daytime::duration duration){
    char buffer[100];
    sprintf(buffer, "%s %2d:%2d %d/%d/%d  - %s %2d:%2d %d/%d/%d", 
    daytime::convertDay(duration.startDay).c_str(), 
    duration.startTime.hour, 
    duration.startTime.minute, 
    duration.startDate.day, 
    duration.startDate.month, 
    duration.startDate.year,
    daytime::convertDay(duration.endDay).c_str(), 
    duration.endTime.hour, 
    duration.endTime.minute, 
    duration.endDate.day, 
    duration.endDate.month, 
    duration.endDate.year);
    return (std::string) buffer;
}

/**
 * @brief  Get time right now
 * @retval value of daytime::time
 */
daytime::time daytime::getTime(){
    time_t now = system_clock::to_time_t(system_clock::now());
    tm *ltm = localtime(&now);

    daytime::time time;
    time.hour = ltm->tm_hour;
    time.minute = ltm->tm_min;
    return time;
}

/**
 * @brief  Get today
 * @retval value in daytime::day
 */
daytime::day daytime::getDay(){
    time_t now = system_clock::to_time_t(system_clock::now());
    tm *ltm = localtime(&now);
    daytime::day day;
    day = static_cast<daytime::day>((ltm->tm_wday+6)%7);
    return day;
}

/**
 * @brief  Get date for today
 * @retval value in daytime::date
 */
daytime::date daytime::getDate(){
    time_t now = system_clock::to_time_t(system_clock::now());
    tm *ltm = localtime(&now);

    daytime::date date;
    date.day = ltm->tm_mday;
    date.month = ltm->tm_mon + 1;
    date.year = ltm->tm_year + 1900;
    return date;
}

/**
 * @brief  Get date in the future 
 * @param  days: days in the future
 * @param  hours: hours in the future
 * @param  minutes: minutes in the future
 * @retval value in daytime::date
 */
daytime::date daytime::getFutureDate(int days, int hours, int minutes){
    system_clock::time_point t = std::chrono::system_clock::now();
    system_clock::time_point new_t = t + std::chrono::minutes(days*24*60 + hours*60 + minutes);

    time_t now = system_clock::to_time_t(new_t);
    tm *ltm = localtime(&now);

    daytime::date date;
    date.day = ltm->tm_mday;
    date.month = ltm->tm_mon + 1;
    date.year = ltm->tm_year + 1900;
    return date;
}