#ifndef _RESPONSE_HANDLER_H
#define _RESPONSE_HANDLER_H

#include "../utilities/constants.h"

void handleQueryRes();
void handleNewBookingRes();
void handleModBookingRes();
void handleNewMonitorRes();
void handleCancelBookingRes();
void handleModMonitorRes();
void handleResponse(int command, char buffer[MAX_BUFFSIZE]);

#endif
