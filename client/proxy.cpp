#include "proxy.h"

char* marshalIntArray();
std::vector<int> unmarshalIntArray();
char* marshalDayTime();
daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();
int unmarshalQueryResponse();

char* marshalQueryReq(std::string facilityName, std::vector<int> days) {
    std::vector<char> queryReq;
    
    queryReq.push_back(facilityName.length());
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(queryReq));
    
    for (std::vector<int>::iterator it = days.begin(); it != days.end(); ++it) {
        queryReq.push_back(*it);
    }
    return queryReq.data();
}

char* marshalNewBookingReq(std::string facilityName, daytime::duration bookDayTime) {
    std::vector<char> bookReq;
    
    bookReq.push_back(facilityName.length());
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(bookReq));
    
    bookReq.push_back(bookDayTime.startDay);
    bookReq.push_back(bookDayTime.startTime.hour);
    bookReq.push_back(bookDayTime.startTime.minute);
    bookReq.push_back(bookDayTime.endDay);
    bookReq.push_back(bookDayTime.endTime.hour);
    bookReq.push_back(bookDayTime.endTime.minute);
    return bookReq.data();
}
