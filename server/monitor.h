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
    daytime::date expiryDate;

    public:
    monitor(struct sockaddr_in clientAddress, daytime::duration duration, daytime::date expiryDate);
    struct sockaddr_in getSocketAddress();
    std::string getIpAddress();
    daytime::duration getDuration();
    daytime::date getExpiryDate();
    void extend(int days, int hours, int minutes);
    void print();
};

#endif