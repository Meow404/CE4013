#ifndef BOOKING
#define BOOKING

#include "daytime.h"
#include "string"

class booking
{
    daytime::duration duration;
    std::string confirmationId;
    std::string generateConfirmationId(std::string ipAddress);

    public:
    booking(std::string ipAddress, daytime::duration duration);
    booking(std::string ipAddress, std::string confirmationId, daytime::duration duration);
    std::string getConfirmationId();

    daytime::duration getDuration();
    void change(int days, int hours, int minutes);
    void extend(int days, int hours, int minutes);
    void print();
};

#endif