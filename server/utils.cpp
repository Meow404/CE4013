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