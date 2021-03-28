#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "booking.h"
#include "../utilities/daytime.h"

using namespace std;

/** Request Format:
 *  <facility name size><facility name>[<s_day><s_hr><s_min>][<e_day><e_hr><e_min>]
 */
void craftNewBookingReq(vector<char> &payload) {
    string bookDaytimePrompt =
    "[DAY] -> 0 = Mon, 1 = Tues, 2 = Wed, 3 = Thurs, 4 = Fri, 5 = Sat, 6 = Sun\n"    \
    "[HOUR] -> 24-hour timing (0 = 12am, 23 = 11pm)\n"   \
    "[MIN] -> 0 to 59\n" \
    "Input start/end day & time as: [DAY] [HOUR] [MIN]\n";
    string startDaytimeStr, endDaytimeStr;
    daytime::duration bookDayTime;
    string facilityName;  // Unknown size so use string instead of char array
    int temp;

    cout << "Facility Name: ";
    std::cin.ignore();
    getline(std::cin, facilityName);
    cout << bookDaytimePrompt;
    cout << "Start Day & Time: ";
    std::cin.ignore();
    getline(std::cin, startDaytimeStr);
    cout << "End Day & Time: ";
    std::cin.ignore();
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
    
    payload.push_back(facilityName.length());
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(payload));
    char *marshalledBookDT = marshalDuration(bookDayTime);
    payload.insert(payload.end(), &marshalledBookDT[0], &marshalledBookDT[23]);
    cout << "PAYLOAD: " << payload.data() << endl;
}

/** Request Format:
 *  <confirmationID>[<c_day><c_hr><c_min>]
 */
void craftModBookingReq(vector<char> &payload) {
    char confirmationID[26];
    char dayOffset, hourOffset, minOffset;

    cout << "Confirmation ID: ";
    cin >> confirmationID;
    cout << "No. Days to Move Booking: ";
    cin >> dayOffset;
    cout << "No. Hours to Move Booking: ";
    cin >> hourOffset;
    cout << "No. Min to Move Booking: ";
    cin >> minOffset;

    // Input Validity check

    char day[4];
    char hour[4];
    char min[4];
    payload.insert(payload.end(), &confirmationID[0], &confirmationID[CID_LENGTH-1]);
    marshalInt(dayOffset, day);
    payload.insert(payload.end(), &day[0], &day[3]);
    marshalInt(hourOffset, hour);
    payload.insert(payload.end(), &hour[0], &hour[3]);
    marshalInt(minOffset, min);
    payload.insert(payload.end(), &min[0], &min[3]);
}

/** Request Format:
 *  <confirmationID>
 */
void craftCancelBookingReq(vector<char> &payload) {
    char confirmationID[26];
    cout << "Confirmation ID: ";
    cin >> confirmationID;

    // Input Validity check

    payload.insert(payload.end(), &confirmationID[0], &confirmationID[25]);
}
