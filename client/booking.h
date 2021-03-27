#ifndef _BOOKING_H_
#define _BOOKING_H_

#include "proxy.h"
#include "../utilities/daytime.h"

char *craftNewBookingReq();
char *craftModBookingReq();
char *craftCancelBookingReq();

#endif