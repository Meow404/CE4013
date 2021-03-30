#ifndef UTILS
#define UTILS

#include <cstring>
#include <ctime>
#include <string>

using namespace std;

void marshalInt(int value, char* message);
void marshalString(string value, char* message);

int unmarshalInt(char* message);
string unmarshalString(char* message, int length);

string genRandom(const int len);

#endif
