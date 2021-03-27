#ifndef _BOOKING_H_
#define _BOOKING_H_

#include <vector>

#include "proxy.h"
#include "../utilities/daytime.h"

std::vector<char> craftNewBookingReq();
std::vector<char> craftModBookingReq();
std::vector<char> craftCancelBookingReq();

#endif