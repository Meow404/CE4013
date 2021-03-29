#include "proxy.h"

void marshalInt(int toMarshal, char marshalled[4]) {
    marshalled[0] = (toMarshal >> 24) & 0xFF;
    marshalled[1] = (toMarshal >> 16) & 0xFF;
    marshalled[2] = (toMarshal >> 8) & 0xFF;
    marshalled[3] = toMarshal & 0xFF;
}

int unmarshalInt(char *message) {
    int value = (message[0] & 0xFF) << 24 | (message[1] & 0xFF) << 16 | (message[2] & 0xFF) << 8 | (message[3] & 0xFF);
    return value;
}

std::string unmarshalString(char *message, int length)
{
    return std::string(message, length);
}

void marshalDuration(daytime::duration dr, char *result) {
    std::vector<char> marshalledDr;
    char day[4];
    char hour[4];
    char min[4];
    marshalInt(dr.startDay, day);
    marshalledDr.insert(marshalledDr.end(), &day[0], &day[4]);
    marshalInt(dr.startTime.hour, hour);
    marshalledDr.insert(marshalledDr.end(), &hour[0], &hour[4]);
    marshalInt(dr.startTime.minute, min);
    marshalledDr.insert(marshalledDr.end(), &min[0], &min[4]);

    // std::cout << "STARTDAY: " << unmarshalInt(day) << std::endl;
    // std::cout << "STARTHOUR: " << unmarshalInt(hour) << std::endl;
    // std::cout << "STARTMIN: " << unmarshalInt(min) << std::endl;

    marshalInt(dr.endDay, day);
    marshalledDr.insert(marshalledDr.end(), &day[0], &day[4]);
    marshalInt(dr.endTime.hour, hour);
    marshalledDr.insert(marshalledDr.end(), &hour[0], &hour[4]);
    marshalInt(dr.endTime.minute, min);
    marshalledDr.insert(marshalledDr.end(), &min[0], &min[4]);

    // std::cout << "ENDDAY: " << unmarshalInt(day) << std::endl;
    // std::cout << "ENDHOUR: " << unmarshalInt(hour) << std::endl;
    // std::cout << "ENDMIN: " << unmarshalInt(min) << std::endl;
    // std::cout << "MARSHALLED SIZE: " << marshalledDr.size() << std::endl;

    for (int i = 0; i < marshalledDr.size(); i++) {
        result[i] = marshalledDr[i];
    }
}

void unmarshalDuration(char *marshalled, daytime::duration *result) {
    int ind = 0;
    result->startDay = daytime::getDay(getInt(marshalled, &ind));
    result->startTime.hour = getInt(marshalled, &ind);
    result->startTime.minute = getInt(marshalled, &ind);
    result->endDay = daytime::getDay(getInt(marshalled, &ind));
    result->endTime.hour = getInt(marshalled, &ind);
    result->endTime.minute = getInt(marshalled, &ind);
}

void unmarshalDurationTimeOnly(char *marshalled, daytime::duration *result) {
    int ind = 0;
    result->startTime.hour = getInt(marshalled, &ind);
    result->startTime.minute = getInt(marshalled, &ind);
    result->endTime.hour = getInt(marshalled, &ind);
    result->endTime.minute = getInt(marshalled, &ind);
}

int getInt(char *buffer, int *index)
{
    int value = unmarshalInt(&buffer[*index]);
    *index += 4;

    return value;
}

std::string getString(char *buffer, int *index)
{
    int size = unmarshalInt(&buffer[*index]);
    *index += 4;

    std::string value = unmarshalString(&buffer[*index], size);
    *index += size;

    return value;
}

void getDuration(char *buffer, int *index, daytime::duration *destination) {
    int size = 24;
    unmarshalDuration(&buffer[*index], destination);
    *index += size;
}

void getDurationTimeOnly(char *buffer, int *index, daytime::duration *destination) {
    int size = 16;
    unmarshalDurationTimeOnly(&buffer[*index], destination);
    *index += size;
}

daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();
int unmarshalQueryResponse();
