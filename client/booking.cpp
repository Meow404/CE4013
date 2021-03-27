#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "booking.h"

using namespace std;

/** Request Format:
 *  <facility name size><facility name>[<s_day><s_hr><s_min>][<e_day><e_hr><e_min>]
 */
char* craftNewBookingReq() {
    string bookDaytimePrompt =
    "[DAY] -> 0 = Mon, 1 = Tues, 2 = Wed, 3 = Thurs, 4 = Fri, 5 = Sat, 6 = Sun"    \
    "[HOUR] -> 24-hour timing (0 = 12am, 23 = 11pm)"   \
    "[MIN] -> 0 to 59" \
    "Input start/end day & time as: [DAY] [HOUR] [MIN]";
    string startDaytimeStr;
    string endDaytimeStr;
    daytime::duration bookDayTime;
    string facilityName;  // Unknown size so use string instead of char array
    int temp;

    cout << "Facility Name: ";
    getline(std::cin, facilityName);
    cout << bookDaytimePrompt;
    cout << "Start Day & Time: ";
    getline(std::cin, startDaytimeStr);
    cout << "End Day & Time: ";
    getline(std::cin, endDaytimeStr);

    istringstream startStm(startDaytimeStr);
    startStm >> temp;
    bookDayTime.startDay = daytime::getDay(temp);
    startStm >> temp;
    bookDayTime.startTime.hour = temp;
    startStm >> temp;
    bookDayTime.startTime.minute = temp;

    istringstream endStm(endDaytimeStr);
    endStm >> temp;
    bookDayTime.endDay = daytime::getDay(temp);
    endStm >> temp;
    bookDayTime.endTime.hour = temp;
    endStm >> temp;
    bookDayTime.endTime.minute = temp;

    // Input Validity check

    return marshalNewBookingReq(facilityName, bookDayTime);
}

/** Request Format:
 *  <confirmationID>[<c_day><c_hr><c_min>]
 */
char* craftModBookingReq() {
    char confirmationID[26];
    char dayOffset;
    char hourOffset;
    char minOffset;

    cout << "Confirmation ID: ";
    cin >> confirmationID;
    cout << "No. Days to Move Booking: ";
    cin >> dayOffset;
    cout << "No. Hours to Move Booking: ";
    cin >> hourOffset;
    cout << "No. Min to Move Booking: ";
    cin >> minOffset;

    // Input Validity check

    return marshalModBookingReq(confirmationID, dayOffset, hourOffset, minOffset);
}
