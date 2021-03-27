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
