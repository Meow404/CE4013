#include "booking.h"
#include "daytime.h"
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

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

booking::booking(string clientId, daytime::duration duration)
{
    this->duration = duration;
    this->confirmationId = generateConfirmationId(clientId);
    this->clientId = clientId;
}

booking::booking(string clientId, string confirmationId, daytime::duration duration)
{
    this->duration = duration;
    if (confirmationId.size() == 0)
        this->confirmationId = generateConfirmationId(clientId);
    else
        this->confirmationId = confirmationId;
}

booking::booking(const booking &obj){
    this->duration = obj.duration;
    this->confirmationId = obj.confirmationId;
    this->clientId = obj.clientId;
}

string booking::getConfirmationId()
{
    return confirmationId;
}

daytime::duration booking::getDuration()
{
    return duration;
}

void booking::updateDuration(daytime::duration duration){
    this->duration = duration;
}

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

void booking::print()
{
    char buffer1[100], buffer2[100];
    sprintf(buffer1, "%s %2d:%2d - %s %2d:%2d", daytime::convertDay(duration.startDay).c_str(), duration.startTime.hour, duration.startTime.minute, daytime::convertDay(duration.endDay).c_str(), duration.endTime.hour, duration.endTime.minute);
    sprintf(buffer2, " %d/%d/%d - %d/%d/%d", duration.startDate.day, duration.startDate.month, duration.startDate.year, duration.endDate.day, duration.endDate.month, duration.endDate.year);
    cout << "confirmation ID : " << confirmationId << " - " << buffer1 << buffer2 << endl;
}