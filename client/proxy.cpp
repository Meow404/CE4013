#include "proxy.h"

void marshalInt(int toMarshal, char marshalled[4]) {
    marshalled[0] = (toMarshal >> 24) & 0xFF;
    marshalled[1] = (toMarshal >> 16) & 0xFF;
    marshalled[2] = (toMarshal >> 8) & 0xFF;
    marshalled[3] = toMarshal & 0xFF;
}

char *marshalDuration(daytime::duration dr) {
    std::vector<char> marshalledDr;
    char day[4];
    char hour[4];
    char min[4];
    marshalInt(dr.startDay, day);
    marshalledDr.insert(marshalledDr.end(), &day[0], &day[3]);
    marshalInt(dr.startTime.hour, hour);
    marshalledDr.insert(marshalledDr.end(), &hour[0], &hour[3]);
    marshalInt(dr.startTime.minute, min);
    marshalledDr.insert(marshalledDr.end(), &min[0], &min[3]);

    marshalInt(dr.endDay, day);
    marshalledDr.insert(marshalledDr.end(), &day[0], &day[3]);
    marshalInt(dr.endTime.hour, hour);
    marshalledDr.insert(marshalledDr.end(), &hour[0], &hour[3]);
    marshalInt(dr.startTime.minute, min);
    marshalledDr.insert(marshalledDr.end(), &min[0], &min[3]);

    return marshalledDr.data();
}

daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();
int unmarshalQueryResponse();
