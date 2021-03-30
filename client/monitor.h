#ifndef _MONITOR_H_
#define _MONITOR_H_

#include <vector>

void setMonitorEndTime(std::chrono::system_clock::time_point &monitorEnd,
                       int days, int hours, int minutes);
void craftNewMonitorReq(std::vector<char> &payload,
                        std::chrono::system_clock::time_point &monitorEnd);

#endif
