#ifndef USAGE_COUNTER_H
#define USAGE_COUNTER_H

#include <mutex>

#include "function_traits.h"


// Used to count current users of a resource.
class usage_counter
{
    std::mutex mutex;
    int value {0};

    template<typename function>
    result_type<function> with_lock(function f)
    {
        std::unique_lock<std::mutex> l {mutex};
        return f();
    }

public:
    usage_counter() {}

    // @return the value of the counter
    int get()
    {
        return with_lock([&](){
                return value;
            });
    }
    // @return true if the resource is in use
    operator bool() { return get(); }

    usage_counter &operator++()
    {
        with_lock([&]() {
                ++value;
            });
        return *this;
    }
    usage_counter &operator--()
    {
        with_lock([&]() {
                --value;
            });
        return *this;
    }
};

#endif // USAGE_COUNTER_H
