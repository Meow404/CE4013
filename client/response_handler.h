#ifndef _RESPONSE_HANDLER_H
#define _RESPONSE_HANDLER_H

#include "../utilities/constants.h"

void handleQueryRes(int day, char buffer[MAX_BUFFSIZE]);
void handleNewBookingRes(char buffer[MAX_BUFFSIZE]);
void handleModBookingRes(char buffer[MAX_BUFFSIZE]);
void handleNewMonitorRes(char buffer[MAX_BUFFSIZE]);
void handleCancelBookingRes(char buffer[MAX_BUFFSIZE]);
void handleModMonitorRes(char buffer[MAX_BUFFSIZE]);
void handleResponse(int command, char buffer[MAX_BUFFSIZE]);

#endif
