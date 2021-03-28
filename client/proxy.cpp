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

char *marshalDuration(daytime::duration dr) {
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

    std::cout << "STARTDAY: " << unmarshalInt(day) << std::endl;
    std::cout << "STARTHOUR" << unmarshalInt(hour) << std::endl;
    std::cout << "STARTMIN" << unmarshalInt(min) << std::endl;

    marshalInt(dr.endDay, day);
    marshalledDr.insert(marshalledDr.end(), &day[0], &day[4]);
    marshalInt(dr.endTime.hour, hour);
    marshalledDr.insert(marshalledDr.end(), &hour[0], &hour[4]);
    marshalInt(dr.startTime.minute, min);
    marshalledDr.insert(marshalledDr.end(), &min[0], &min[4]);

    std::cout << "STARTDAY: " << unmarshalInt(day) << std::endl;
    std::cout << "STARTHOUR" << unmarshalInt(hour) << std::endl;
    std::cout << "STARTMIN" << unmarshalInt(min) << std::endl;

    return marshalledDr.data();
}

daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();
int unmarshalQueryResponse();
