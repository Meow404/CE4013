#include "proxy.h"

char *marshalInt(int toMarshal) {
    char marshalled[4];
    marshalled[0] = (toMarshal >> 24) & 0xFF;
    marshalled[1] = (toMarshal >> 16) & 0xFF;
    marshalled[2] = (toMarshal >> 8) & 0xFF;
    marshalled[3] = toMarshal & 0xFF;
    return marshalled;
}

char *marshalDuration(daytime::duration dr) {
    std::vector<char> marshalledDr;
    char *startDay = marshalInt(dr.startDay);
    marshalledDr.insert(marshalledDr.end(), &startDay[0], &startDay[3]);
    char *startHour = marshalInt(dr.startTime.hour);
    marshalledDr.insert(marshalledDr.end(), &startHour[0], &startHour[3]);
    char *startMin = marshalInt(dr.startTime.minute);
    marshalledDr.insert(marshalledDr.end(), &startMin[0], &startMin[3]);

    char *endDay = marshalInt(dr.endDay);
    marshalledDr.insert(marshalledDr.end(), &endDay[0], &endDay[3]);
    char *endHour = marshalInt(dr.endTime.hour);
    marshalledDr.insert(marshalledDr.end(), &endHour[0], &endHour[3]);
    char *endMin = marshalInt(dr.startTime.minute);
    marshalledDr.insert(marshalledDr.end(), &endMin[0], &endMin[3]);

    return marshalledDr.data();
}

daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();
int unmarshalQueryResponse();
