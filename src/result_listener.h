#ifndef RESULT_LISTENER_H
#define RESULT_LISTENER_H

#include "config.h"

#include <thread>
#include <mutex>
#include <condition_variable>

/*!
 * A template for a MegaListener.
 * Used to wait for the end of an operation and get its result.
 *
 * Subclass must call set_result() at some point
 * for wait_for_result() to return.
 */
template<typename result_type> class result_listener
{
    result_type result;
    bool done = false;

    std::condition_variable cond;
    std::mutex done_mutex;

protected:
    void set_result(result_type result)
    {
        std::unique_lock<std::mutex> lock{done_mutex};
        this->result = move(result);
        done = true;
        cond.notify_all();
    }

public:
    result_type wait_for_result()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock{done_mutex};
            if (done)
                break;
            cond.wait(lock);
        }

        return move(result);
    }
};

#endif // RESULT_LISTENER_H
