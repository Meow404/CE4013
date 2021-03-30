#ifndef BOOKING
#define BOOKING

#include "daytime.h"
#include "string"

/**
 * @brief  Booking object holds relevant booking information
 */
class booking
{
    daytime::duration duration;
    std::string confirmationId;
    std::string clientId;
    std::string generateConfirmationId(std::string clientId);

    public:
    booking(std::string clientId, daytime::duration duration);
    booking(std::string clientId, std::string confirmationId, daytime::duration duration);
    booking(const booking &obj);
    std::string getConfirmationId();

    daytime::duration getDuration();
    void updateDuration(daytime::duration duration);
    void change(int days, int hours, int minutes);
    void extend(int days, int hours, int minutes);
    void print();
};

#endif