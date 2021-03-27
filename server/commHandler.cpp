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

string commHandler::getString(char *buffer, int *index)
{
    int size = unmarshalInt(&buffer[*index]);
    *index += SIZE_INT;

    string value = unmarshalString(&buffer[*index], size);
    *index += size;

    cout << value << endl;
    return value;
}

void commHandler::setInt(char *buffer, int *index, int value)
{
    buffer[(*index)++] = 'd';
    marshalInt(value, &buffer[*index]);
    *index += SIZE_INT;
}
void commHandler::setString(char *buffer, int *index, string value)
{
    buffer[(*index)++] = 's';
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

    status = FM->addFacilityBooking(server->getClientIP(), &confirmationId, facility_name, s_day, s_hour, s_minute, e_day, e_hour, e_minute);

    index = 0;
    setInt(buffer, &index, status);
    if (status == 0)
    {
        setString(buffer, &index, confirmationId);
    }
    server->sendMessage(buffer, index);
}

void commHandler::handleChangeBooking(char *buffer, int index)
{
    int status, days, hours, minutes;
    string confirmationId;

    confirmationId = getString(buffer, &index);
    cout << "Havent reached here yet";
    days = getInt(buffer, &index);
    hours = getInt(buffer, &index);
    minutes = getInt(buffer, &index);

    status = FM->changeFacilityBooking(server->getClientIP(), &confirmationId, days, hours, minutes);

    index = 0;
    setInt(buffer, &index, status);
    if (status == 0)
    {
        setString(buffer, &index, confirmationId);
    }
    server->sendMessage(buffer, index);
}


void commHandler::handleExtendBooking(char *buffer, int index)
{
    int status, days, hours, minutes;
    string confirmationId;

    confirmationId = getString(buffer, &index);
    days = getInt(buffer, &index);
    hours = getInt(buffer, &index);
    minutes = getInt(buffer, &index);

    status = FM->extendFacilityBooking(server->getClientIP(), &confirmationId, days, hours, minutes);

    index = 0;
    setInt(buffer, &index, status);
    if (status == 0)
    {
        setString(buffer, &index, confirmationId);
    }
    server->sendMessage(buffer, index);
}


void commHandler::handleCancelBooking(char *buffer, int index)
{
    string confirmationId;
    bool status;

    confirmationId = getString(buffer, &index);
    status = FM->cancelFacilityBooking(confirmationId);

    index = 0;
    setInt(buffer, &index, status);
    server->sendMessage(buffer, index);
}



void commHandler::start()
{
    char buffer[BUFFER_SIZE];
    int funNum, index;
    while (true)
    {
        index = 0;
        server->recieveMessage(buffer, BUFFER_SIZE);

        funNum = getInt(buffer, &index);

        switch (funNum)
        {
        case 1:
            break;
        case 2:
            handleAddBooking(buffer, index);
            break;
        case 3:
            handleChangeBooking(buffer, index);
            break;
        case 4:
            break;
        case 5:
            handleExtendBooking(buffer, index);
            break;
        case 6:
            handleCancelBooking(buffer, index);
        default:
            break;
        }
    }
}
