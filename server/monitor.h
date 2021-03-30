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

    public:
    monitor(struct sockaddr_in clientAddress, daytime::duration duration);
    struct sockaddr_in getSocketAddress();
    std::string getIpAddress();
    daytime::duration getDuration();
    void extend(int days, int hours, int minutes);
    void print();
};

#endif