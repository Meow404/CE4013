#ifndef COMMHANDLER
#define COMMHANDLER

#define SIZE_INT 4

#include "udpServer.h"
#include "facilityManager.h"
#include "facility.h"
#include "utils.h"
#include "daytime.h"
#include "monitor.h"
#include <thread>
#include <iostream>

using namespace std;

class commHandler
{
    udpServer* server;
    facilityManager* FM;

    int getInt(char * buffer, int* index);
    string getString(char * buffer, int* index);
    void setInt(char * buffer, int* index, int value);
    void setString(char * buffer, int* index, string value);
    void setDuration(char * buffer, int* index, daytime::duration value);

    public:
    commHandler(udpServer* server, facilityManager* facility_manager);
    void handleUpdateMonitors(facility* facility, char * buffer, int* index);
    void handleGetFaciltiyNames(char * buffer, int* index);
    void handleAddMonitor(char * buffer, int* index);
    void handleGetAvailability(char * buffer, int* index);
    void handleAddBooking(char * buffer, int* index);
    void handleChangeBooking(char * buffer, int* index);
    void handleExtendBooking(char * buffer, int* index);
    void handleCancelBooking(char * buffer, int* index);
    void handleAllFunctions(void);
    void start();

};

#endif
