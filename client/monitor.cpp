#include <iostream>
#include <string>
#include <vector>

#include "monitor.h"

using namespace std;

/** Request Format:
 *  <facility name size><facility name>[<m_day><m_hr><m_min>]
 */
char* craftNewMonitorReq() {
    string facilityName;
    int days, hours, minutes;
    vector<char> monitorReq;

    cout << "Facility Name: ";
    getline(std::cin, facilityName);
    cout << "No. Days to Monitor: ";
    cin >> days;
    cout << "No. Hours to Monitor (Max 23): ";
    cin >> hours;
    cout << "No. Min to Monitor (Max 60): ";
    cin >> minutes;

    // Input Validity check

    monitorReq.push_back(facilityName.length());
    copy(facilityName.begin(), facilityName.end(), back_inserter(monitorReq));
    monitorReq.push_back(days);
    monitorReq.push_back(hours);
    monitorReq.push_back(minutes);
    return monitorReq.data();
}

/** Request Format:
 *  <facility name size><facility name>[<e_day><e_hr><e_min>]
 */
char* craftModMonitorReq() {
    string facilityName;
    int days, hours, minutes;
    vector<char> modMonitorReq;

    cout << "Facility Name: ";
    getline(std::cin, facilityName);
    cout << "No. Days to Extend Monitor: ";
    cin >> days;
    cout << "No. Hours to Extend Monitor (Max 23): ";
    cin >> hours;
    cout << "No. Min to Extend Monitor (Max 60): ";
    cin >> minutes;

    // Input Validity check

    modMonitorReq.push_back(facilityName.length());
    copy(facilityName.begin(), facilityName.end(), back_inserter(modMonitorReq));
    modMonitorReq.push_back(days);
    modMonitorReq.push_back(hours);
    modMonitorReq.push_back(minutes);
    return modMonitorReq.data();
}
