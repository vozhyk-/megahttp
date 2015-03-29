#ifndef LISTENER_BASE_H
#define LISTENER_BASE_H

#include <thread>
#include <chrono>

template<typename result_type> class listener_base
{
public:
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
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        return result;
    }
};

#endif // LISTENER_BASE_H
