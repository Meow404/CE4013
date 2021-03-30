#include "booking.h"
#include "daytime.h"
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/**
 * @brief  Generates unique confirmation ID for booking by making use of client Id, data & time of booking
 * @param  clientId: Unique ID provided to each client
 * @retval unique confirmation ID generated for each booking
 */
string booking::generateConfirmationId(string clientId)
{

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[26];

    sprintf(buffer, "%12s%04d%02d%02d%02d%02d%02d", clientId.c_str(),
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec);

    string confirmationId = buffer;
    return confirmationId;
}

/**
 * @brief  Created an instance of booking with the help of client Id and booking duration
 * @param  clientId: Unique ID provided to each client
 * @param  duration: Duration of booking
 * @retval None
 */
booking::booking(string clientId, daytime::duration duration)
{
    this->duration = duration;
    this->confirmationId = generateConfirmationId(clientId);
    this->clientId = clientId;
}

/**
 * @brief  Created an instance of booking with the help of client Id and booking duration
 * @param  clientId: Unique ID provided to each client
 * @param  duration: Duration of booking
 * @param  confirmationId: Previous confirmation ID if applicable
 * @retval None
 */
booking::booking(string clientId, string confirmationId, daytime::duration duration)
{
    this->duration = duration;
    if (confirmationId.size() == 0)
        this->confirmationId = generateConfirmationId(clientId);
    else
        this->confirmationId = confirmationId;
}

/**
 * @brief  Copy constructor to copy one booking object to another
 * @param  &obj: booking object to be copied
 * @retval None
 */
booking::booking(const booking &obj){
    this->duration = obj.duration;
    this->confirmationId = obj.confirmationId;
    this->clientId = obj.clientId;
}

/**
 * @brief  Returns confirmation ID
 * @retval confirmation ID
 */
string booking::getConfirmationId()
{
    return confirmationId;
}

/**
 * @brief  Returns booking duration
 * @retval duration of booking
 */
daytime::duration booking::getDuration()
{
    return duration;
}

/**
 * @brief  Update duration of booking
 * @param  duration: new duration of booking
 * @retval None
 */
void booking::updateDuration(daytime::duration duration){
    this->duration = duration;
}

/**
 * @brief  Change booking duration by time specified (shifting the booking)
 * @param  days: number of days to be changed by
 * @param  hours: number of hours to be changed by
 * @param  minutes: number of minutes to be changed by
 * @retval None
 */
void booking::change(int days, int hours, int minutes)
{
    daytime::day today = daytime::getDay();

    duration.startTime.minute += minutes;
    duration.startTime.hour += hours + duration.startTime.minute / 60;
    duration.startDay = static_cast<daytime::day>((duration.startDay + days + duration.startTime.hour / 24) % 7);
    duration.startTime.minute %= 60;
    duration.startTime.hour %= 24;
    duration.startDate = daytime::getFutureDate((duration.startDay + 7 - today) % 7, 0, 0);
    

    duration.endTime.minute += minutes;
    duration.endTime.hour += hours + duration.endTime.minute / 60;
    duration.endDay = static_cast<daytime::day>((duration.endDay + days + duration.endTime.hour / 24) % 7);
    duration.endTime.minute %= 60;
    duration.endTime.hour %= 24;
    duration.endDate = daytime::getFutureDate((duration.endDay + 7 - today) % 7, 0, 0);
}

/**
 * @brief  Extend booking duration by some time
 * @param  days: number of days to be extended by
 * @param  hours: number of hours to be extended by
 * @param  minutes: numbed to minuted to be extended by
 * @retval None
 */
void booking::extend(int days, int hours, int minutes)
{
    daytime::day today = daytime::getDay();

    duration.endTime.minute += minutes;
    duration.endTime.hour += hours + duration.endTime.minute / 60;
    duration.endDay = static_cast<daytime::day>((duration.endDay + days + duration.endTime.hour / 24) % 7);
    duration.endTime.minute %= 60;
    duration.endTime.hour %= 24;
    duration.endDate = daytime::getFutureDate((duration.endDay + 7 - today) % 7, 0, 0);
}

/**
 * @brief  Print booking information
 * @retval None
 */
void booking::print()
{
    char buffer[100];
    sprintf(buffer, "%s %2d:%2d %d/%d/%d  - %s %2d:%2d %d/%d/%d", 
    daytime::convertDay(duration.startDay).c_str(), 
    duration.startTime.hour, 
    duration.startTime.minute, 
    duration.startDate.day, 
    duration.startDate.month, 
    duration.startDate.year,
    daytime::convertDay(duration.endDay).c_str(), 
    duration.endTime.hour, 
    duration.endTime.minute, 
    duration.endDate.day, 
    duration.endDate.month, 
    duration.endDate.year);
    cout << "confirmation ID : " << confirmationId << " : " << buffer  << endl;
}