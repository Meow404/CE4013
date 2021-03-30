#include "utils.h"

/**
 * @brief  Marshal an integer
 * @param  value: integer to be marshalled
 * @param  message: messaged in which marshalled int is to be stored
 * @retval None
 */
void marshalInt(int value, char *message)
{
    message[0] = (value >> 24) & 0xFF;
    message[1] = (value >> 16) & 0xFF;
    message[2] = (value >> 8) & 0xFF;
    message[3] = value & 0xFF;
}

/**
 * @brief  Marshal a string
 * @param  value: string value to be marshalled
 * @param  message: message in which string is marshalled
 * @retval None
 */
void marshalString(string value, char *message)
{
    strcpy(message, value.c_str());
}

/**
 * @brief  Unmarshall integer from the message
 * @param  message: buffer that stores the integer 
 * @retval unmarshalled integer
 */
int unmarshalInt(char *message)
{
    int value = (message[0] & 0xFF) << 24 | (message[1] & 0xFF) << 16 | (message[2] & 0xFF) << 8 | (message[3] & 0xFF);
    return value;
}

/**
 * @brief  Unmarshal string from the message
 * @param  message: message containing string
 * @param  length: length of the string
 * @retval unmarshalled string
 */
string unmarshalString(char *message, int length)
{
    return string(message, length);
}

/**
 * @brief  Generate random alphanumeric string
 * @note   used for client ID
 * @param  len: len of random string
 * @retval random string
 */
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