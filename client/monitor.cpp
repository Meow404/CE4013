#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "monitor.h"
#include "proxy.h"

void setMonitorEndTime(std::chrono::system_clock::time_point &monitorEnd,
                      int days, int hours, int minutes) {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::minutes durationInMin = std::chrono::minutes(days*24*60 + hours*60 + minutes);
    monitorEnd = now + durationInMin;
}

/** Request Format:
 *  <facility name size><facility name>[<m_day><m_hr><m_min>]
 */
void craftNewMonitorReq(std::vector<char> &payload,
                        std::chrono::system_clock::time_point &monitorEnd) {
    std::string facilityName;
    int days, hours, minutes;

    std::cout << "\nFacility Name: ";
    std::cin.ignore();
    getline(std::cin, facilityName);
    std::cout << "No. Days to Monitor: ";
    std::cin >> days;
    if (std::cin.fail()) return;
    std::cout << "No. Hours to Monitor (Max 23): ";
    std::cin >> hours;
    if (std::cin.fail()) return;
    std::cout << "No. Min to Monitor (Max 59): ";
    std::cin >> minutes;
    if (std::cin.fail()) return;

    // Input Validity check
    if (days > 6 || days < 0 || hours > MAX_HR ||
        hours < 0 || minutes > MAX_MINUTES || minutes < 0) {
        std::cerr << "Invalid Time Value\n" << std::endl;
        return;
    }

    setMonitorEndTime(monitorEnd, days, hours, minutes);

    char facNameSize[4];
    marshalInt(facilityName.length(), facNameSize);
    payload.insert(payload.end(), &facNameSize[0], &facNameSize[4]);
    copy(facilityName.begin(), facilityName.end(), back_inserter(payload));
    
    char dayBytes[4];
    char hourBytes[4];
    char minBytes[4];    
    marshalInt(days, dayBytes);
    payload.insert(payload.end(), &dayBytes[0], &dayBytes[4]);
    marshalInt(hours, hourBytes);
    payload.insert(payload.end(), &hourBytes[0], &hourBytes[4]);
    marshalInt(minutes, minBytes);
    payload.insert(payload.end(), &minBytes[0], &minBytes[4]);
}
