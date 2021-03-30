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
    // buffer[(*index)++] = 'd';
    marshalInt(value, &buffer[*index]);
    *index += SIZE_INT;
}
void commHandler::setString(char *buffer, int *index, string value)
{
    // buffer[(*index)++] = 's';
    marshalInt(value.size(), &buffer[*index]);
    *index += SIZE_INT;
    marshalString(value, &buffer[*index]);
    *index += value.size();
}
void commHandler::setDuration(char *buffer, int *index, daytime::duration value)
{
    // buffer[(*index)++] = 't';
    setInt(buffer, index, value.startTime.hour);
    setInt(buffer, index, value.startTime.minute);
    setInt(buffer, index, value.endTime.hour);
    setInt(buffer, index, value.endTime.minute);
}

void commHandler::handleUpdateMonitors(facility *facility, char *buffer, int *index)
{
    int startIndex = *index;

    vector<monitor> monitors = facility->getMonitors();
    for (int day = 0; day < 7; day++)
    {
        std::vector<daytime::duration> availabilities = FM->getFacilityAvailability(facility, day);
        setInt(buffer, index, day);
        setInt(buffer, index, availabilities.size());
        for (int i = 0; i < availabilities.size(); i++)
        {
            setDuration(buffer, index, availabilities[i]);
            if (*index >= BUFFER_SIZE - 20)
            {
                for (int j = 0; j < monitors.size(); j++)
                {
                    server->sendMessageToClient(buffer, *index, monitors[j].getSocketAddress());
                }
                *index = startIndex;
            }
        }
    }
    if (*index > startIndex)
        for (int j = 0; j < monitors.size(); j++)
        {
            server->sendMessageToClient(buffer, *index, monitors[j].getSocketAddress());
        }
}

void commHandler::handleAddMonitor(char *buffer, int *index)
{
    int status, days, hours, minutes;
    string facility_name;

    facility_name = getString(buffer, index);
    days = getInt(buffer, index);
    hours = getInt(buffer, index);
    minutes = getInt(buffer, index);

    facility *facility = FM->getFacility(facility_name);
    status = FM->addMonitorForFacility(facility, server->getClientSocketAddress(), days, hours, minutes);

    *index = 0;
    setInt(buffer, index, status);
    server->sendMessage(buffer, *index);
}

void commHandler::handleGetAvailability(char *buffer, int *index)
{
    int status, day;
    string facility_name, confirmationId;

    facility_name = getString(buffer, index);
    day = getInt(buffer, index);

    *index = 0;
    if (FM->isFacility(facility_name))
    {
        facility *facility = FM->getFacility(facility_name);
        std::vector<daytime::duration> availabilities = FM->getFacilityAvailability(facility, day);
        setInt(buffer, index, 0);
        setInt(buffer, index, availabilities.size());
        for (int i = 0; i < availabilities.size(); i++)
        {
            setDuration(buffer, index, availabilities[i]);
        }
    }
    else
    {
        setInt(buffer, index, 1);
    }
    server->sendMessage(buffer, *index);
}

void commHandler::handleAddBooking(char *buffer, int *index)
{
    int status, s_day, s_hour, s_minute, e_day, e_hour, e_minute;
    string facility_name, confirmationId;

    facility_name = getString(buffer, index);
    s_day = getInt(buffer, index);
    s_hour = getInt(buffer, index);
    s_minute = getInt(buffer, index);
    e_day = getInt(buffer, index);
    e_hour = getInt(buffer, index);
    e_minute = getInt(buffer, index);

    facility *facility = FM->getFacility(facility_name);
    status = FM->addFacilityBooking(server->getClientIP(), &confirmationId, facility, s_day, s_hour, s_minute, e_day, e_hour, e_minute);

    *index = 0;
    setInt(buffer, index, status);
    if (status == 0)
    {
        setString(buffer, index, confirmationId);
    }
    server->sendMessage(buffer, *index);

    if (status == 0)
    {
        *index = 0;
        setInt(buffer, index, 1);
        handleUpdateMonitors(facility, buffer, index);
    }
}

void commHandler::handleChangeBooking(char *buffer, int *index)
{
    int status, days, hours, minutes;
    string confirmationId;

    confirmationId = getString(buffer, index);
    cout << "Havent reached here yet" << endl;
    days = getInt(buffer, index);
    hours = getInt(buffer, index);
    minutes = getInt(buffer, index);

    facility *facility = FM->getBookingFacility(confirmationId);
    status = FM->changeFacilityBooking(server->getClientIP(), &confirmationId, facility, days, hours, minutes);

    *index = 0;
    setInt(buffer, index, status);
    if (status == 0)
    {
        setString(buffer, index, confirmationId);
    }
    server->sendMessage(buffer, *index);

    if (status == 0)
    {
        *index = 0;
        setInt(buffer, index, 3);
        handleUpdateMonitors(facility, buffer, index);
    }
}

void commHandler::handleExtendBooking(char *buffer, int *index)
{
    int status, days, hours, minutes;
    string confirmationId;

    confirmationId = getString(buffer, index);
    days = getInt(buffer, index);
    hours = getInt(buffer, index);
    minutes = getInt(buffer, index);

    facility *facility = FM->getBookingFacility(confirmationId);
    status = FM->extendFacilityBooking(server->getClientIP(), &confirmationId, facility, days, hours, minutes);

    *index = 0;
    setInt(buffer, index, status);
    if (status == 0)
    {
        setString(buffer, index, confirmationId);
    }
    server->sendMessage(buffer, *index);

    if (status == 0)
    {
        *index = 0;
        setInt(buffer, index, 2);
        handleUpdateMonitors(facility, buffer, index);
    }
}

void commHandler::handleCancelBooking(char *buffer, int *index)
{
    string confirmationId;
    bool status;

    confirmationId = getString(buffer, index);
    facility *facility = FM->getBookingFacility(confirmationId);
    status = FM->cancelFacilityBooking(confirmationId, facility);

    *index = 0;
    setInt(buffer, index, !status);
    server->sendMessage(buffer, *index);

    if (status == 0)
    {
        *index = 0;
        setInt(buffer, index, 4);
        handleUpdateMonitors(facility, buffer, index);
    }
}

void commHandler::handleAllFunctions()
{
    char buffer[BUFFER_SIZE];
    int funNum, index, messageType, reqId;

    index = 0;
    server->recieveMessage(buffer, BUFFER_SIZE);

    messageType = getInt(buffer, &index);
    reqId = getInt(buffer, &index);

    if (!server->resendReply(reqId))
    {

        funNum = getInt(buffer, &index);

        switch (funNum)
        {
        case 1:
            handleGetAvailability(buffer, &index);
            break;
        case 2:
            handleAddBooking(buffer, &index);
            break;
        case 3:
            handleChangeBooking(buffer, &index);
            break;
        case 4:
            handleAddMonitor(buffer, &index);
            break;
        case 5:
            handleExtendBooking(buffer, &index);
            break;
        case 6:
            handleCancelBooking(buffer, &index);
        default:
            break;
        }
        server->addReply(reqId, buffer, index);
    }
}

void commHandler::start()
{

    while (true)
    {
        handleAllFunctions();
    }
}
