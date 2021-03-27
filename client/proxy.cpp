#include "proxy.h"

char* marshalDuration(daytime::duration dr) {
    char message[6];
    message[0] = dr.startDay;
    message[1] = dr.startTime.hour;
    message[2] = dr.startTime.minute;
    message[3] = dr.endDay;
    message[4] = dr.endTime.hour;
    message[5] = dr.endTime.minute;
}

daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();
int unmarshalQueryResponse();
