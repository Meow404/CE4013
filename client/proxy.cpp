#include "proxy.h"

/**
 * @brief  Convert int to byte representation
 * @param  toMarshal Input int to marshal
 * @param  marshalled char array to store byte conversion result
 * @retval None
 */
void marshalInt(int toMarshal, char marshalled[4]) {
    marshalled[0] = (toMarshal >> 24) & 0xFF;
    marshalled[1] = (toMarshal >> 16) & 0xFF;
    marshalled[2] = (toMarshal >> 8) & 0xFF;
    marshalled[3] = toMarshal & 0xFF;
}

/**
 * @brief  Convert byte representation back to int
 * @param  message Byte message to convert to int
 * @retval int value of byte representation
 */
int unmarshalInt(char *message) {
    int value = (message[0] & 0xFF) << 24 | (message[1] & 0xFF) << 16 | (message[2] & 0xFF) << 8 | (message[3] & 0xFF);
    return value;
}

/**
 * @brief  Convert byte representation back to string
 * @param  message Byte message to convert to string
 * @param  length Length of string result
 * @retval string value of byte representation
 */
std::string unmarshalString(char *message, int length)
{
    return std::string(message, length);
}

/**
 * @brief  Convert daytime::duration object to byte representation
 * @param  dr daytime::duration object to convert
 * @param  result char array to store byte conversion result
 * @retval None
 */
void marshalDuration(daytime::duration dr, char *result) {
    std::vector<char> marshalledDr;
    char day[4];
    char hour[4];
    char min[4];
    marshalInt(dr.startDay, day);
    marshalledDr.insert(marshalledDr.end(), &day[0], &day[4]);
    marshalInt(dr.startTime.hour, hour);
    marshalledDr.insert(marshalledDr.end(), &hour[0], &hour[4]);
    marshalInt(dr.startTime.minute, min);
    marshalledDr.insert(marshalledDr.end(), &min[0], &min[4]);

    // std::cout << "STARTDAY: " << unmarshalInt(day) << std::endl;
    // std::cout << "STARTHOUR: " << unmarshalInt(hour) << std::endl;
    // std::cout << "STARTMIN: " << unmarshalInt(min) << std::endl;

    marshalInt(dr.endDay, day);
    marshalledDr.insert(marshalledDr.end(), &day[0], &day[4]);
    marshalInt(dr.endTime.hour, hour);
    marshalledDr.insert(marshalledDr.end(), &hour[0], &hour[4]);
    marshalInt(dr.endTime.minute, min);
    marshalledDr.insert(marshalledDr.end(), &min[0], &min[4]);

    // std::cout << "ENDDAY: " << unmarshalInt(day) << std::endl;
    // std::cout << "ENDHOUR: " << unmarshalInt(hour) << std::endl;
    // std::cout << "ENDMIN: " << unmarshalInt(min) << std::endl;
    // std::cout << "MARSHALLED SIZE: " << marshalledDr.size() << std::endl;

    for (int i = 0; i < marshalledDr.size(); i++) {
        result[i] = marshalledDr[i];
    }
}

/**
 * @brief  Set fields of a daytime::duration object from byte representation
 * @param  marshalled Byte message to convert to daytime::duration
 * @param  result Target daytime::duration object to set fields of
 * @retval None
 */
void unmarshalDuration(char *marshalled, daytime::duration *result) {
    int ind = 0;
    result->startDay = daytime::getDay(getInt(marshalled, &ind));
    result->startTime.hour = getInt(marshalled, &ind);
    result->startTime.minute = getInt(marshalled, &ind);
    result->endDay = daytime::getDay(getInt(marshalled, &ind));
    result->endTime.hour = getInt(marshalled, &ind);
    result->endTime.minute = getInt(marshalled, &ind);
}

/**
 * @brief  Set time fields of a daytime::duration object from byte representation
 * @param  marshalled Byte message to convert to daytime::duration time fields
 * @param  result Target daytime::duration object to set fields of
 * @retval None
 */
void unmarshalDurationTimeOnly(char *marshalled, daytime::duration *result) {
    int ind = 0;
    result->startTime.hour = getInt(marshalled, &ind);
    result->startTime.minute = getInt(marshalled, &ind);
    result->endTime.hour = getInt(marshalled, &ind);
    result->endTime.minute = getInt(marshalled, &ind);
}

/**
 * @brief  Extract an int value from byte buffer
 * @param  buffer Byte buffer to extract int from
 * @param  index Index in buffer to extract int from
 * @retval int value extracted
 */
int getInt(char *buffer, int *index)
{
    int value = unmarshalInt(&buffer[*index]);
    *index += 4;

    return value;
}

/**
 * @brief  Extract a string value from byte buffer
 * @param  buffer Byte buffer to extract string from
 * @param  index Index in buffer to extract string from
 * @retval string value extracted
 */
std::string getString(char *buffer, int *index)
{
    int size = unmarshalInt(&buffer[*index]);
    *index += 4;

    std::string value = unmarshalString(&buffer[*index], size);
    *index += size;

    return value;
}

/**
 * @brief  Extract a daytime::duration from byte buffer
 * @param  buffer Byte buffer to extract daytime::duration from
 * @param  index Index in buffer to extract daytime::duration from
 * @retval None
 */
void getDuration(char *buffer, int *index, daytime::duration *destination) {
    int size = 24;
    unmarshalDuration(&buffer[*index], destination);
    *index += size;
}

/**
 * @brief  Extract time fields of daytime::duration from byte buffer
 * @param  buffer Byte buffer to extract daytime::duration time fields from
 * @param  index Index in buffer to extract daytime::duration time fields from
 * @retval None
 */
void getDurationTimeOnly(char *buffer, int *index, daytime::duration *destination) {
    int size = 16;
    unmarshalDurationTimeOnly(&buffer[*index], destination);
    *index += size;
}

daytime::day unmarshalDay();
daytime::time unmarshalTime();
daytime::duration unmarshalDuration();
int unmarshalQueryResponse();
