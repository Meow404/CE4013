#ifndef _PROXY_H_
#define _PROXY_H_

#include <iostream>
#include <string>
#include <vector>
#include "../utilities/daytime.h"

char* marshalIntArray();
std::vector<int> unmarshalIntArray();
char* marshalDayTime();
daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();

char* marshalQueryReq(std::string facilityName, std::vector<int> days);
char* marshalNewBookingReq(std::string facilityName, daytime::duration bookDayTime);

int unmarshalQueryResponse();

#endif
