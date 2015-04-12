#ifndef LISTENER_BASE_H
#define LISTENER_BASE_H

#include "config.h"

#include <thread>

template<typename result_type> class listener_base
{
public:
    /* done and result can be set from outside. Make private? */
    bool done;
    result_type result;

    listener_base()
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

        return result;
    }
};

#endif // LISTENER_BASE_H
