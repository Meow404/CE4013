#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "booking.h"

char* craftNewBookingReq() {
    std::string bookDaytimePrompt =
    "[DAYS] -> 0 = Mon, 1 = Tues, 2 = Wed, 3 = Thurs, 4 = Fri, 5 = Sat, 6 = Sun"    \
    "[HOURS] -> 24-hour timing (0 = 12am, 23 = 11pm)"   \
    "[MIN] -> 0 to 59" \
    "Input start/end day & time as: [DAYS] [HOURS] [MIN]";
    std::string startDaytimeStr;
    std::string endDaytimeStr;
    daytime::duration bookDayTime;
    std::string facilityName;  // Unknown size so use string instead of char array
    int temp;

    std::cout << "Facility Name: ";
    std::getline(std::cin, facilityName);
    std::cout << bookDaytimePrompt;
    std::cout << "Start Day & Time: ";
    std::getline(std::cin, startDaytimeStr);
    std::cout << "End Day & Time: ";
    std::getline(std::cin, endDaytimeStr);

    std::istringstream startStm(startDaytimeStr);
    startStm >> temp;
    bookDayTime.startDay = daytime::getDay(temp);
    startStm >> temp;
    bookDayTime.startTime.hour = temp;
    startStm >> temp;
    bookDayTime.startTime.minute = temp;

    std::istringstream endStm(endDaytimeStr);
    endStm >> temp;
    bookDayTime.endDay = daytime::getDay(temp);
    endStm >> temp;
    bookDayTime.endTime.hour = temp;
    endStm >> temp;
    bookDayTime.endTime.minute = temp;

    // Input Validity check

    return marshalNewBookingReq(facilityName, bookDayTime);
}
//<facility name size><facility name>[<s_day><s_hr><s_min>][<e_day><e_hr><e_min>]