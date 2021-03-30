#include "monitor.h"

using namespace std;

/**
 * @brief  Monitor constructor
 * @param  clientAddress: socket address of client
 * @param  duration: duration of monitoring period
 * @retval None
 */
monitor::monitor(sockaddr_in clientAddress, daytime::duration duration)
{
    this->clientAddress = clientAddress;
    this->duration = duration;
}

/**
 * @brief  Get the socket address of the client
 * @retval socket address of the client
 */
struct sockaddr_in monitor::getSocketAddress()
{
    return clientAddress;
}

/**
 * @brief  Get IP Address of the client
 * @retval IP Address of the client
 */
string monitor::getIpAddress()
{
    char *ip = inet_ntoa(clientAddress.sin_addr);
    return (string)ip;
}

/**
 * @brief  Extend monitoring period
 * @param  days: days by which monitoring period is extended
 * @param  hours: hours by which monitoring period is extended
 * @param  minutes: minutes by which monitoring period is extended
 * @retval None
 */
void monitor::extend(int days, int hours, int minutes)
{
    duration.endTime.minute += minutes;
    duration.endTime.hour += hours + duration.endTime.minute / 60;
    duration.endDay = static_cast<daytime::day>((duration.endDay + days + duration.endTime.hour / 24) % 7);
    duration.endTime.minute %= 60;
    duration.endTime.hour %= 24;
}

/**
 * @brief  Get duration of monitoring period
 * @retval duration
 */
daytime::duration monitor::getDuration()
{
    return duration;
}

/**
 * @brief  Print monitoring information
 * @retval None
 */
void monitor::print()
{
    char buffer1[100], buffer2[100];
    sprintf(buffer1, "%s %2d:%2d - %s %2d:%2d", daytime::convertDay(duration.startDay).c_str(), duration.startTime.hour, duration.startTime.minute, daytime::convertDay(duration.endDay).c_str(), duration.endTime.hour, duration.endTime.minute);
    sprintf(buffer2, "%d/%d/%d", duration.endDate.day, duration.endDate.month, duration.endDate.year);
    cout << "ipAddress : " << getIpAddress() << " - "<< buffer1 << " Expiration date : "<< buffer2 << endl;
}
