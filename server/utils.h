#ifndef UTILS
#define UTILS

#include <string>
#include <stdio.h>

using namespace std;

void marshalInt(int value, char* message);
void marshalString(string value, char* message);

int unmarshalInt(char* message);
string unmarshalString(char* message, int length);

#endif
