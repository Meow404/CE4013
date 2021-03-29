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
    if (cin.fail()) return;
    cout << "No. Hours to Monitor (Max 23): ";
    cin >> hours;
    if (cin.fail()) return;
    cout << "No. Min to Monitor (Max 59): ";
    cin >> minutes;
    if (cin.fail()) return;

    // Input Validity check
    if (days > 6 || days < 0 || hours > MAX_HR ||
        hours < 0 || minutes > MAX_MINUTES || minutes < 0) {
        cerr << "Invalid Time Value\n" << endl;
        return;
    }

    char dayBytes[4];
    char hourBytes[4];
    char minBytes[4];
    payload.push_back(facilityName.length());
    copy(facilityName.begin(), facilityName.end(), back_inserter(payload));
    marshalInt(days, dayBytes);
    payload.insert(payload.end(), &dayBytes[0], &dayBytes[4]);
    marshalInt(hours, hourBytes);
    payload.insert(payload.end(), &hourBytes[0], &hourBytes[4]);
    marshalInt(minutes, minBytes);
    payload.insert(payload.end(), &minBytes[0], &minBytes[4]);
}
