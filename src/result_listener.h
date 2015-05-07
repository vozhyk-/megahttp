#ifndef RESULT_LISTENER_H
#define RESULT_LISTENER_H

#include "config.h"

#include <thread>
#include <future>

/*!
 * A template for a MegaListener.
 * Used to wait for the end of an operation and get its result.
 *
 * Subclass must set promise's value at some point
 * for wait_for_result() to return.
 */
template<typename result_type> class result_listener
{
    result_type result;
    bool done = false;

protected:
    std::promise<result_type> promise;

public:
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
