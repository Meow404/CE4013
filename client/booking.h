#ifndef _BOOKING_H_
#define _BOOKING_H_

#include <vector>

#include "proxy.h"

void craftNewBookingReq(std::vector<char> &payload);
void craftModBookingReq(std::vector<char> &payload);
void craftCancelBookingReq(std::vector<char> &payload);

#endif