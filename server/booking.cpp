#include "booking.h"
#include "daytime.h"
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

string booking::generateConfirmationId(string ipAddress)
{
    string delimiter = ".";
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();

    string token;
    vector<int> ipVectors;

    while ((pos_end = ipAddress.find(delimiter, pos_start)) != string::npos)
    {
        token = ipAddress.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        ipVectors.push_back(stoi(token));
    }

    ipVectors.push_back(stoi(ipAddress.substr(pos_start)));

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[26];

    sprintf(buffer, "%03d%03d%03d%03d%04d%02d%02d%02d%02d%02d", ipVectors[0],
            ipVectors[1],
            ipVectors[2],
            ipVectors[3],
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec);

    string confirmationId = buffer;
    return confirmationId;
}

booking::booking(string ipAddress, daytime::duration duration)
{
    this->duration = duration;
    this->confirmationId = generateConfirmationId(ipAddress);
}

booking::booking(string ipAddress, string confirmationId, daytime::duration duration)
{
    this->duration = duration;
    if (confirmationId.size() == 0)
        this->confirmationId = generateConfirmationId(ipAddress);
    else
        this->confirmationId = confirmationId;
}

string booking::getConfirmationId()
{
    return confirmationId;
}

daytime::duration booking::getDuration()
{
    return duration;
}

void booking::change(int days, int hours, int minutes)
{
    duration.startTime.minute += minutes;
    duration.startTime.hour += hours + duration.startTime.minute / 60;
    duration.startDay = static_cast<daytime::day>((duration.startDay + days + duration.startTime.hour / 24) % 7);
    duration.startTime.minute %= 60;
    duration.startTime.hour %= 24;

    duration.endTime.minute += minutes;
    duration.endTime.hour += hours + duration.endTime.minute / 60;
    duration.endDay = static_cast<daytime::day>((duration.endDay + days + duration.endTime.hour / 24) % 7);
    duration.endTime.minute %= 60;
    duration.endTime.hour %= 24;
}
void booking::extend(int days, int hours, int minutes)
{
    duration.endTime.minute += minutes;
    duration.endTime.hour += hours + duration.endTime.minute / 60;
    duration.endDay = static_cast<daytime::day>((duration.endDay + days + duration.endTime.hour / 24) % 7);
    duration.endTime.minute %= 60;
    duration.endTime.hour %= 24;
}

void booking::print()
{
    char buffer[20];
    sprintf(buffer, "%s %2d:%2d - %s %2d:%2d", daytime::convertDay(duration.startDay).c_str(), duration.startTime.hour, duration.startTime.minute, daytime::convertDay(duration.endDay).c_str(), duration.endTime.hour, duration.endTime.minute);
    cout << "confirmation ID : " << confirmationId << " - "<< buffer << endl;
}