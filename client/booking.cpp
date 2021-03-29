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
    "\n[DAY] -> 0 = Mon, 1 = Tues, 2 = Wed, 3 = Thurs, 4 = Fri, 5 = Sat, 6 = Sun\n"    \
    "[HOUR] -> 24-hour timing (0 = 12am, 23 = 11pm)\n"   \
    "[MIN] -> 0 to 59\n" \
    "Input start/end day & time as: [DAY] [HOUR] [MIN]\n";
    string startDaytimeStr, endDaytimeStr;
    daytime::duration bookDayTime;
    string facilityName;  // Unknown size so use string instead of char array
    int temp;

    cout << "\nFacility Name: ";
    cin.ignore();
    getline(cin, facilityName);
    cout << bookDaytimePrompt;

    cout << "\nStart Day & Time: ";
    getline(cin, startDaytimeStr);
    istringstream startStm(startDaytimeStr);
    if (!startStm) {
        cerr << "ERROR: Invalid Day & Time Format\n";
        return;
    }
    startStm >> temp;
    bookDayTime.startDay = daytime::getDay(temp);
    if (bookDayTime.startDay == daytime::INVALID) {
        cerr << "ERROR: Invalid Day!\n";
        return;
    }
    if (!startStm) {
        cerr << "ERROR: Invalid Day & Time Format\n";
        return;
    }
    startStm >> temp;
    bookDayTime.startTime.hour = temp;
    if (!startStm) {
        cerr << "ERROR: Invalid Day & Time Format\n";
        return;
    }
    startStm >> temp;
    bookDayTime.startTime.minute = temp;

    cout << "End Day & Time: ";
    getline(cin, endDaytimeStr);
    istringstream endStm(endDaytimeStr);
    if (!endStm) {
        cerr << "ERROR: Invalid Day & Time Format\n";
        return;
    }
    endStm >> temp;
    bookDayTime.endDay = daytime::getDay(temp);
    if (bookDayTime.startDay == daytime::INVALID) {
        cerr << "ERROR: Invalid Day!\n";
        return;
    }
    if (!endStm) {
        cerr << "ERROR: Invalid Day & Time Format\n";
        return;
    }
    endStm >> temp;
    bookDayTime.endTime.hour = temp;
    if (!endStm) {
        cerr << "ERROR: Invalid Day & Time Format\n";
        return;
    }
    endStm >> temp;
    bookDayTime.endTime.minute = temp;

    // Input Validity checks
    if (bookDayTime.startTime.hour > MAX_HR || bookDayTime.endTime.hour > MAX_HR) {
        cerr << "ERROR: Hour specified is more than maximum 23\n";
        return;
    }
    if (bookDayTime.startTime.minute > MAX_MINUTES || bookDayTime.endTime.minute > MAX_MINUTES) {
        cerr << "ERROR: Minute specified is more than maximum 59\n";
        return;
    }
    
    char facNameSize[4];
    marshalInt(facilityName.length(), facNameSize);
    payload.insert(payload.end(), &facNameSize[0], &facNameSize[4]);
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(payload));
    
    char marshalledBookDT[24];
    marshalDuration(bookDayTime, marshalledBookDT);
    payload.insert(payload.end(), &marshalledBookDT[0], &marshalledBookDT[24]);
}

/** Request Format:
 *  <confirmationID>[<c_day><c_hr><c_min>]
 */
void craftShiftBookingReq(vector<char> &payload) {
    char confirmID[26];
    int dayOffset, hourOffset, minOffset;

    cout << "Confirmation ID: ";
    cin >> confirmID;
    cout << "No. Days to Shift Booking: ";
    cin >> dayOffset;
    if (cin.fail()) return;
    cout << "No. Hours to Shift Booking: ";
    cin >> hourOffset;
    if (cin.fail()) return;
    cout << "No. Min to Shift Booking: ";
    cin >> minOffset;
    if (cin.fail()) return;

    // Input Validity check
    if (dayOffset > 6 || dayOffset < 0 || hourOffset > MAX_HR ||
        hourOffset < 0 || minOffset > MAX_MINUTES || minOffset < 0) {
        cerr << "Invalid Time Value\n" << endl;
        return;
    }

    char cidLen[4];
    char day[4];
    char hour[4];
    char min[4];

    marshalInt(26, cidLen);
    payload.insert(payload.end(), &cidLen[0], &cidLen[4]);
    payload.insert(payload.end(), &confirmID[0], &confirmID[CID_LENGTH]);

    marshalInt(dayOffset, day);
    payload.insert(payload.end(), &day[0], &day[4]);
    marshalInt(hourOffset, hour);
    payload.insert(payload.end(), &hour[0], &hour[4]);
    marshalInt(minOffset, min);
    payload.insert(payload.end(), &min[0], &min[4]);
}

/** Request Format:
 *  <confirmationID>
 */
void craftCancelBookingReq(vector<char> &payload) {
    char confirmID[26];
    cout << "Confirmation ID: ";
    cin >> confirmID;

    char cidLen[4];
    marshalInt(26, cidLen);
    payload.insert(payload.end(), &cidLen[0], &cidLen[4]);
    payload.insert(payload.end(), &confirmID[0], &confirmID[CID_LENGTH]);
}

/** Request Format:
 *  <confirmationID>[<e_day><e_hr><e_min>]
 */
void craftExtendBookingReq(std::vector<char> &payload) {
    char confirmID[26];
    int dayOffset, hourOffset, minOffset;

    cout << "Confirmation ID: ";
    cin >> confirmID;
    cout << "No. Days to Extend Booking: ";
    cin >> dayOffset;
    if (cin.fail()) return;
    cout << "No. Hours to Extend Booking: ";
    cin >> hourOffset;
    if (cin.fail()) return;
    cout << "No. Min to Extend Booking: ";
    cin >> minOffset;
    if (cin.fail()) return;

    // Input Validity check
    if (dayOffset > 6 || dayOffset < 0 || hourOffset > MAX_HR ||
        hourOffset < 0 || minOffset > MAX_MINUTES || minOffset < 0) {
        cerr << "Invalid Time Value\n" << endl;
        return;
    }

    char cidLen[4];
    char day[4];
    char hour[4];
    char min[4];

    marshalInt(26, cidLen);
    payload.insert(payload.end(), &cidLen[0], &cidLen[4]);
    payload.insert(payload.end(), &confirmID[0], &confirmID[CID_LENGTH]);

    marshalInt(dayOffset, day);
    payload.insert(payload.end(), &day[0], &day[4]);
    marshalInt(hourOffset, hour);
    payload.insert(payload.end(), &hour[0], &hour[4]);
    marshalInt(minOffset, min);
    payload.insert(payload.end(), &min[0], &min[4]);
}
