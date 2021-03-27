#include "commHandler.h"

commHandler::commHandler(udpServer *server, facilityManager *facility_manager)
{
    this->server = server;
    this->FM = facility_manager;
}

int commHandler::getInt(char *buffer, int *index)
{
    int value = unmarshalInt(&buffer[*index]);
    *index += SIZE_INT;

    cout << value << endl;
    return value;
}

string getString(char *buffer, int *index)
{
    int size = unmarshalInt(&buffer[*index]);
    *index += SIZE_INT;

    string value = unmarshalString(&buffer[*index], size);
    *index += size;

    cout << value << endl;
    return value;
}

void setInt(char * buffer, int* index, int value){
    buffer[*index++] = 'd';
    marshalInt(value, &buffer[*index]);
    *index += SIZE_INT;
}
void setString(char * buffer, int* index, string value){
    buffer[*index++] = 's';
    marshalInt(value.size(), &buffer[*index]);
    *index += SIZE_INT;
    marshalString(value, &buffer[*index]);
    *index += value.size();
}

void commHandler::handleAddBooking(char *buffer, int index)
{
    int status, s_day, s_hour, s_minute, e_day, e_hour, e_minute;
    string facility_name, confirmationId;

    facility_name = getString(buffer, &index);
    s_day = getInt(buffer, &index);
    s_hour = getInt(buffer, &index);
    s_minute = getInt(buffer, &index);
    e_day = getInt(buffer, &index);
    e_hour = getInt(buffer, &index);
    e_minute = getInt(buffer, &index);

    status = FM->addFacilityBooking(server.getClientIP(), &confirmationId, facility_name, s_day, s_hour, s_minute, e_day, e_hour, e_minute);

    index = 0;
    setInt(buffer, &index, status);
    if (status == 0)
    {
        setString(buffer, &index, confirmationId);
    }
    server->sendMessage(buffer, BUFFER_SIZE);
}

void commHandler::start()
{
    char buffer[BUFFER_SIZE];
    int funNum, index = 0;
    server->recieveMessage(buffer, BUFFER_SIZE);

    funNum = unmarshalInt(&buffer[index]);
    index += SIZE_INT;

    switch (funNum)
    {
    case 1:
        break;
    case 2:
        handleAddBooking(buffer, index);
        break;

    default:
        break;
    }
}
