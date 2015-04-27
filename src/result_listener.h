#ifndef RESULT_LISTENER_H
#define RESULT_LISTENER_H

#include "config.h"

#include <thread>
#include <future>

template<typename result_type> class result_listener
{
    result_type result;
    bool done = false;

protected:
    std::promise<result_type> promise;

public:
    /* Subclass must set promise's value at some point */

    result_type wait_for_result()
    {
        if (!done)
        {
            result = promise.get_future().get();
            done = true;
        }

        return move(result);
    }
};

#endif // RESULT_LISTENER_H
