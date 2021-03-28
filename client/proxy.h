#ifndef _PROXY_H_
#define _PROXY_H_

#include <iostream>
#include <string>
#include <vector>
#include "../utilities/constants.h"
#include "../utilities/daytime.h"

void marshalInt(int toMarshal, char marshalled[4]);
int unmarshalInt(char *message);
std::string unmarshalString(char *message, int length);
void marshalDuration(daytime::duration dr, char *marshalled);
int getInt(char *buffer, int *index);
std::string getString(char *buffer, int *index);

daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();

int unmarshalQueryResponse();

#endif
