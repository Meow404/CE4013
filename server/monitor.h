#ifndef MONITOR
#define MONITOR

#include "daytime.h"

class monitor
{
    daytime::duration duration;
    char* ipAddress;
    int port;

    public:
    monitor(char* ipAddress, int port, daytime::duration duration);
    char* getIpAddress();
    int getPort();
    void extend(int days, int hours, int minutes);
};

#endif