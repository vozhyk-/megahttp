#ifndef RESULT_LISTENER_H
#define RESULT_LISTENER_H

#include "config.h"

#include <thread>
#include <future>

template<typename result_type> class result_listener
{
protected:
    std::promise<result_type> promise;

public:
    /* Subclass must set promise's value at some point */

    result_type wait_for_result()
    {
        return move(promise.get_future().get());
    }
};

#endif // RESULT_LISTENER_H
