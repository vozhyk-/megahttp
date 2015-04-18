#ifndef RESULT_LISTENER_H
#define RESULT_LISTENER_H

#include "config.h"

#include <thread>

template<typename result_type> class result_listener
{
public:
    /* done and result can be set from outside. Make private? */
    bool done;
    result_type result;

    result_listener()
    {
        done = false;
        result = {};
    }

    result_type wait_for_result()
    {
        while (!done)
        {
            std::this_thread::sleep_for(mega_request_sleep);
        }

        return move(result);
    }
};

#endif // RESULT_LISTENER_H
