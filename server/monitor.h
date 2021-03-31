#ifndef MONITOR
#define MONITOR

#include "daytime.h"
#include "string"
#include "iostream"
#include <WinSock2.h>

class monitor
{
    daytime::duration duration;
    struct sockaddr_in clientAddress;
    int reqId;

    public:
    monitor(int reqId, struct sockaddr_in clientAddress, daytime::duration duration);
    struct sockaddr_in getSocketAddress();
    std::string getIpAddress();
    daytime::duration getDuration();
    int getReqId();
    void extend(int days, int hours, int minutes);
    void print();
};

#endif