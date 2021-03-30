#include "monitor.h"

using namespace std;

monitor::monitor(sockaddr_in clientAddress, daytime::duration duration, daytime::date expiryDate)
{
    this->clientAddress = clientAddress;
    this->duration = duration;
    this->expiryDate = expiryDate;
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

daytime::date monitor::getExpiryDate(){
    return expiryDate;
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

void monitor::print()
{
    char buffer1[100], buffer2[100];
    sprintf(buffer1, "%s %2d:%2d - %s %2d:%2d", daytime::convertDay(duration.startDay).c_str(), duration.startTime.hour, duration.startTime.minute, daytime::convertDay(duration.endDay).c_str(), duration.endTime.hour, duration.endTime.minute);
    sprintf(buffer2, "%d/%d/%d", expiryDate.day, expiryDate.month, expiryDate.year);
    cout << "ipAddress : " << getIpAddress() << " - "<< buffer1 << " Expiration date : "<< buffer2 << endl;
}
