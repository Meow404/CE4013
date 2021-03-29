#include "monitor.h"

using namespace std;

monitor::monitor(sockaddr_in clientAddress, daytime::duration duration)
{
    this->clientAddress = clientAddress;
    this->duration = duration;
}
struct sockaddr_in monitor::getSocketAddress()
{
    return clientAddress;
}
string monitor::getIpAddress()
{
    char *ip = inet_ntoa(clientAddress.sin_addr);
    return (string)ip;
}
void monitor::extend(int days, int hours, int minutes)
{
    duration.endTime.minute += minutes;
    duration.endTime.hour += hours + duration.endTime.minute / 60;
    duration.endDay = static_cast<daytime::day>((duration.endDay + days + duration.endTime.hour / 24) % 7);
    duration.endTime.minute %= 60;
    duration.endTime.hour %= 24;
}

daytime::duration monitor::getDuration()
{
    return duration;
}
