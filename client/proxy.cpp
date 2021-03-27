#include "proxy.h"

char* marshalIntArray();
std::vector<int> unmarshalIntArray();
char* marshalDayTime();
daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();
int unmarshalQueryResponse();

/** Message Format:
 *  <facility name size><facility name><list of days>
 */
char* marshalQueryReq(std::string facilityName, std::vector<int> days) {
    std::vector<char> queryReq;
    
    queryReq.push_back(facilityName.length());
    std::copy(facilityName.begin(), facilityName.end(), std::back_inserter(queryReq));
    
    for (std::vector<int>::iterator it = days.begin(); it != days.end(); ++it) {
        queryReq.push_back(*it);
    }
    return queryReq.data();
}

/** Message Format:
 *  <facility name size><facility name>[<s_day><s_hr><s_min>][<e_day><e_hr><e_min>]
 */
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

/** Message Format:
 *  <confirmationID>[<c_day><c_hr><c_min>]
 */
char* marshalModBookingReq(char* confirmationID, char dayOffset, char hourOffset, char minOffset)
{
    char modBookReq[CID_LENGTH + 3];
    for (int i = 0; i < 26; i++) {
        modBookReq[i] = confirmationID[i];
    }
    modBookReq[CID_LENGTH] = dayOffset;
    modBookReq[CID_LENGTH + 1] = hourOffset;
    modBookReq[CID_LENGTH + 2] = minOffset;
    return modBookReq;
}
