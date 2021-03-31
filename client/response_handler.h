#ifndef _RESPONSE_HANDLER_H
#define _RESPONSE_HANDLER_H

#include "../utilities/constants.h"

void handleQueryRes(int day, char buffer[MAX_BUFFSIZE], int reqId);
void handleGetFacNames(char buffer[MAX_BUFFSIZE], int reqId);
void handleNewBookingRes(char buffer[MAX_BUFFSIZE], int reqId);
void handleShiftBookingRes(char buffer[MAX_BUFFSIZE], int reqId);
void handleNewMonitorRes(char buffer[MAX_BUFFSIZE], int reqId);
void handleCancelBookingRes(char buffer[MAX_BUFFSIZE], int reqId);
void handleExtendBookingRes(char buffer[MAX_BUFFSIZE], int reqId);
void handleResponse(int command, char buffer[MAX_BUFFSIZE], int reqId);
void handleMonitorNotify(char buffer[MAX_BUFFSIZE]);

#endif
