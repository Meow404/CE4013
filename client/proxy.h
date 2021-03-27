#ifndef _PROXY_H_
#define _PROXY_H_

#include <winsock.h>
#include <vector>
#include "../utilities/daytime.h"

unsigned char* marshalIntArray();
std::vector<int> unmarshalIntArray();
unsigned char* marshalDayTime();
daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();

#endif
