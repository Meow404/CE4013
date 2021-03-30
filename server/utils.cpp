#include "utils.h"

void marshalInt(int value, char *message)
{
    message[0] = (value >> 24) & 0xFF;
    message[1] = (value >> 16) & 0xFF;
    message[2] = (value >> 8) & 0xFF;
    message[3] = value & 0xFF;
}

void marshalString(string value, char *message)
{
    strcpy(message, value.c_str());
}

int unmarshalInt(char *message)
{
    int value = (message[0] & 0xFF) << 24 | (message[1] & 0xFF) << 16 | (message[2] & 0xFF) << 8 | (message[3] & 0xFF);
    return value;
}
string unmarshalString(char *message, int length)
{
    return string(message, length);
}

string genRandom(const int len) {
    
    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    srand(time(NULL));

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) 
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    
    
    return tmp_s;
}