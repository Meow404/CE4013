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
void unmarshalDuration(char *marshalled, daytime::duration *result);
void unmarshalDurationTimeOnly(char *marshalled, daytime::duration *result);

int getInt(char *buffer, int *index);
std::string getString(char *buffer, int *index);
void getDuration(char *buffer, int *index, daytime::duration *destination);
void getDurationTimeOnly(char *buffer, int *index, daytime::duration *destination);

daytime::day unmarshalDay();
daytime::time unmarshalTime();

int unmarshalQueryResponse();

#endif
