#ifndef _CONSTANTS_H_
#define _CONSTANTS_H

#define CID_LENGTH 26
#define MAX_HR 23
#define MAX_MINUTES 59

namespace requests
{  
    enum request
    {
        INVALID,
        QUERY,
        NEW_BOOK,
        MOD_BOOK,
        NEW_MONITOR,
        CANCEL_BOOK,
        MOD_MONITOR,
        EXIT
    };
}

#endif
