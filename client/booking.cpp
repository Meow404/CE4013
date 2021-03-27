#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "booking.h"

using namespace std;

/** Request Format:
 *  <facility name size><facility name>[<s_day><s_hr><s_min>][<e_day><e_hr><e_min>]
 */
vector<char> craftNewBookingReq() {
    string bookDaytimePrompt =
    "[DAY] -> 0 = Mon, 1 = Tues, 2 = Wed, 3 = Thurs, 4 = Fri, 5 = Sat, 6 = Sun"    \
    "[HOUR] -> 24-hour timing (0 = 12am, 23 = 11pm)"   \
    "[MIN] -> 0 to 59" \
    "Input start/end day & time as: [DAY] [HOUR] [MIN]";
    string startDaytimeStr, endDaytimeStr;
    daytime::duration bookDayTime;
    string facilityName;  // Unknown size so use string instead of char array
    std::vector<char> bookReq;
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
    
    bookReq.push_back(facilityName.length());
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(bookReq));
    char *marshalledBookDT = marshalDuration(bookDayTime);
    bookReq.insert(bookReq.end(), &marshalledBookDT[0], &marshalledBookDT[23]);

    return bookReq;
}

/** Request Format:
 *  <confirmationID>[<c_day><c_hr><c_min>]
 */
vector<char> craftModBookingReq() {
    char confirmationID[26];
    char dayOffset, hourOffset, minOffset;
    vector<char> modBookReq;

    cout << "Confirmation ID: ";
    cin >> confirmationID;
    cout << "No. Days to Move Booking: ";
    cin >> dayOffset;
    cout << "No. Hours to Move Booking: ";
    cin >> hourOffset;
    cout << "No. Min to Move Booking: ";
    cin >> minOffset;

    // Input Validity check

    modBookReq.insert(modBookReq.end(), &confirmationID[0], &confirmationID[CID_LENGTH-1]);
    char *day = marshalInt(dayOffset);
    modBookReq.insert(modBookReq.end(), &day[0], &day[3]);
    char *hour = marshalInt(hourOffset);
    modBookReq.insert(modBookReq.end(), &hour[0], &hour[3]);
    char *min = marshalInt(minOffset);
    modBookReq.insert(modBookReq.end(), &min[0], &min[3]);

    return modBookReq;
}

/** Request Format:
 *  <confirmationID>
 */
vector<char> craftCancelBookingReq() {
    char confirmationID[26];
    cout << "Confirmation ID: ";
    cin >> confirmationID;

    // Input Validity check
    
    return vector<char>(confirmationID, confirmationID + 26);
}