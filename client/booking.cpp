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
    cin.ignore();
    getline(cin, facilityName);
    cout << bookDaytimePrompt;
    cout << "Start Day & Time: ";
    getline(cin, startDaytimeStr);
    cout << "End Day & Time: ";
    getline(cin, endDaytimeStr);

    istringstream startStm(startDaytimeStr);
    startStm >> temp;
    bookDayTime.startDay = daytime::getDay(temp);
    // if (bookDayTime.startDay == daytime::INVALID) {
    //     perror("Invalid Day!\n");
    //     exit(1);
    // }
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
    
    char facNameSize[4];
    marshalInt(facilityName.length(), facNameSize);
    payload.insert(payload.end(), &facNameSize[0], &facNameSize[4]);
    cout << "FACILITY NAME SIZE: " << unmarshalInt(facNameSize) << endl;
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(payload));
    
    char marshalledBookDT[24];
    marshalDuration(bookDayTime, marshalledBookDT);
    payload.insert(payload.end(), &marshalledBookDT[0], &marshalledBookDT[24]);
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
