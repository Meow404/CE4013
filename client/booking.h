#ifndef _BOOKING_H_
#define _BOOKING_H_

#include <vector>

#include "proxy.h"

void craftNewBookingReq(std::vector<char> &payload);
void craftShiftBookingReq(std::vector<char> &payload);
void craftCancelBookingReq(std::vector<char> &payload);
void craftExtendBookingReq(std::vector<char> &payload);

#endif