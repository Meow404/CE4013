#ifndef _QUERY_H_
#define _QUERY_H_

#include <vector>
#include <deque>

#include "proxy.h"

void getQueryInput(std::string &facilityName, std::deque<int> &queryDays);
void craftQueryReq(std::vector<char> &payload, std::string facilityName, int day);

#endif
