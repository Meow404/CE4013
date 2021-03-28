#include <iostream>
#include <string>
#include <vector>

#include "monitor.h"
#include "proxy.h"

using namespace std;

/** Request Format:
 *  <facility name size><facility name>[<m_day><m_hr><m_min>]
 */
void craftNewMonitorReq(std::vector<char> &payload) {
    string facilityName;
    int days, hours, minutes;

    cout << "Facility Name: ";
    cin.ignore();
    getline(std::cin, facilityName);
    cout << "No. Days to Monitor: ";
    cin >> days;
    cout << "No. Hours to Monitor (Max 23): ";
    cin >> hours;
    cout << "No. Min to Monitor (Max 60): ";
    cin >> minutes;

    // Input Validity check

    char dayBytes[4];
    char hourBytes[4];
    char minBytes[4];
    payload.push_back(facilityName.length());
    copy(facilityName.begin(), facilityName.end(), back_inserter(payload));
    marshalInt(days, dayBytes);
    payload.insert(payload.end(), &dayBytes[0], &dayBytes[3]);
    marshalInt(hours, hourBytes);
    payload.insert(payload.end(), &hourBytes[0], &hourBytes[3]);
    marshalInt(minutes, minBytes);
    payload.insert(payload.end(), &minBytes[0], &minBytes[3]);
}

/** Request Format:
 *  <facility name size><facility name>[<e_day><e_hr><e_min>]
 */
void craftModMonitorReq(std::vector<char> &payload) {
    string facilityName;
    int days, hours, minutes;

    cout << "Facility Name: ";
    cin.ignore();
    getline(std::cin, facilityName);
    cout << "No. Days to Extend Monitor: ";
    cin >> days;
    cout << "No. Hours to Extend Monitor (Max 23): ";
    cin >> hours;
    cout << "No. Min to Extend Monitor (Max 60): ";
    cin >> minutes;

    // Input Validity check

    char dayBytes[4];
    char hourBytes[4];
    char minBytes[4];
    payload.push_back(facilityName.length());
    copy(facilityName.begin(), facilityName.end(), back_inserter(payload));
    marshalInt(days, dayBytes);
    payload.insert(payload.end(), &dayBytes[0], &dayBytes[3]);
    marshalInt(hours, hourBytes);
    payload.insert(payload.end(), &hourBytes[0], &hourBytes[3]);
    marshalInt(minutes, minBytes);
    payload.insert(payload.end(), &minBytes[0], &minBytes[3]);
}
