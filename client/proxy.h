#ifndef _PROXY_H_
#define _PROXY_H_

#include <iostream>
#include <string>
#include <vector>
#include "../utilities/constants.h"
#include "../utilities/daytime.h"

void marshalInt(int toMarshal, char marshalled[4]);
char *marshalDuration(daytime::duration dr);
daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();

int unmarshalQueryResponse();

#endif
