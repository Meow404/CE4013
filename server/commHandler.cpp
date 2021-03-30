#include "commHandler.h"

/**
 * @brief  communication handler constructor
 * @param  server: UDP server
 * @param  facility_manager: facility manager
 * @retval None
 */
commHandler::commHandler(udpServer *server, facilityManager *facility_manager)
{
    this->server = server;
    this->FM = facility_manager;
}

/**
 * @brief  Unmarshal integer  
 * @param  buffer: buffer in which int is stored
 * @param  index: index of buffer in which integer is stored
 * @retval unmarshalled int
 */
int commHandler::getInt(char *buffer, int *index)
{
    int value = unmarshalInt(&buffer[*index]);
    *index += SIZE_INT;

    cout << value << endl;
    return value;
}

/**
 * @brief  Unmarshal string  
 * @param  buffer: buffer in which string is stored
 * @param  index: index of buffer in which string is stored
 * @retval unmarshalled string
 */
string commHandler::getString(char *buffer, int *index)
{
    int size = unmarshalInt(&buffer[*index]);
    *index += SIZE_INT;

    string value = unmarshalString(&buffer[*index], size);
    *index += size;

    cout << value << endl;
    return value;
}

/**
 * @brief  Marshall integer into the message
 * @param  buffer: message in which integer is stored
 * @param  index: index from which value is to be stored
 * @param  value: value of int
 * @retval None
 */
void commHandler::setInt(char *buffer, int *index, int value)
{
    // buffer[(*index)++] = 'd';
    marshalInt(value, &buffer[*index]);
    *index += SIZE_INT;
}

/**
 * @brief  Marshall string into the message
 * @param  buffer: message in which string is stored
 * @param  index: index from which value is to be stored
 * @param  value: value of string
 * @retval None
 */
void commHandler::setString(char *buffer, int *index, string value)
{
    // buffer[(*index)++] = 's';
    marshalInt(value.size(), &buffer[*index]);
    *index += SIZE_INT;
    marshalString(value, &buffer[*index]);
    *index += value.size();
}

/**
 * @brief  Marshall duration into the message
 * @param  buffer: message in which duration is stored
 * @param  index: index from which duration is to be stored
 * @param  value: value of duration
 * @retval None
 */
void commHandler::setDuration(char *buffer, int *index, daytime::duration value)
{
    // buffer[(*index)++] = 't';
    setInt(buffer, index, value.startTime.hour);
    setInt(buffer, index, value.startTime.minute);
    setInt(buffer, index, value.endTime.hour);
    setInt(buffer, index, value.endTime.minute);
}

/**
 * @brief  Update monitors of a facility 
 * @param  facility: pointer to facility of which monitors is to be updated
 * @param  buffer: message to be sent to monitors
 * @param  index: index from which buffer starts
 * @retval None
 */
void commHandler::handleUpdateMonitors(facility *facility, char *buffer, int *index)
{
    int startIndex = *index;

    vector<monitor> monitors = facility->getMonitors();
    if (monitors.size() != 0)
    {
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
}

/**
 * @brief  Add monitor for the facility 
 * @param  buffer: to store message
 * @param  index: index from which message is to be stored
 * @retval None
 */
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

/**
 * @brief  Get availabilities of a facility 
 * @param  buffer: to store message
 * @param  index: index from which message is to be stored
 * @retval None
 */
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

/**
 * @brief  Add a booking for a facility 
 * @param  buffer: to store message
 * @param  index: index from which message is to be stored
 * @retval None
 */
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

/**
 * @brief  Change a booking of a facility 
 * @param  buffer: to store message
 * @param  index: index from which message is to be stored
 * @retval None
 */
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

/**
 * @brief  extend the booking of a facility 
 * @param  buffer: to store message
 * @param  index: index from which message is to be stored
 * @retval None
 */
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

/**
 * @brief  cancel booking of a facility 
 * @param  buffer: to store message
 * @param  index: index from which message is to be stored
 * @retval None
 */
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

/**
 * @brief  Get names of all facilities 
 * @param  buffer: to store message
 * @param  index: index from which message is to be stored
 * @retval None
 */
void commHandler::handleGetFaciltiyNames(char *buffer, int *index)
{
    vector<string> facilityNames = FM->getFacilityNames();
    *index = 0;
    setInt(buffer, index, facilityNames.size());
    for (int i = 0; i < facilityNames.size(); i++)
        setString(buffer, index, facilityNames[i]);
    server->sendMessage(buffer, *index);
}

/**
 * @brief  Handle all functions 
 * @retval None
 */
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
            break;
        case 7:
            handleAddMonitor(buffer, &index);
            break;
        default:
            break;
        }
        server->addReply(reqId, buffer, index);
    }
}

/**
 * @brief  Start command handling
 * @retval None
 */
void commHandler::start()
{

    while (true)
    {
        handleAllFunctions();
    }
}
