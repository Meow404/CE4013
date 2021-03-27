#include <iostream>
#include <string>
#include <vector>

#include "monitor.h"
#include "proxy.h"

using namespace std;

/** Request Format:
 *  <facility name size><facility name>[<m_day><m_hr><m_min>]
 */
vector<char> craftNewMonitorReq() {
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
    char *dayBytes = marshalInt(days);
    monitorReq.insert(monitorReq.end(), &dayBytes[0], &dayBytes[3]);
    char *hourBytes = marshalInt(hours);
    monitorReq.insert(monitorReq.end(), &hourBytes[0], &hourBytes[3]);
    char *minBytes = marshalInt(minutes);
    monitorReq.insert(monitorReq.end(), &minBytes[0], &minBytes[3]);
    return monitorReq;
}

/** Request Format:
 *  <facility name size><facility name>[<e_day><e_hr><e_min>]
 */
vector<char> craftModMonitorReq() {
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
    modMonitorReq.push_back(facilityName.length());
    copy(facilityName.begin(), facilityName.end(), back_inserter(modMonitorReq));
    char *dayBytes = marshalInt(days);
    modMonitorReq.insert(modMonitorReq.end(), &dayBytes[0], &dayBytes[3]);
    char *hourBytes = marshalInt(hours);
    modMonitorReq.insert(modMonitorReq.end(), &hourBytes[0], &hourBytes[3]);
    char *minBytes = marshalInt(minutes);
    modMonitorReq.insert(modMonitorReq.end(), &minBytes[0], &minBytes[3]);
    return modMonitorReq;
}
