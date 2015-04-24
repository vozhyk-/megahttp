#ifndef USAGE_COUNTER_H
#define USAGE_COUNTER_H

#include <mutex>

// Used to count current users of a resource.
class usage_counter
{
    std::mutex mutex;
    int value {0};

public:
    usage_counter() {}

    // TODO use mutex

    int get() { return value; }
    // @return true if the resource is in use
    operator bool() { return get(); }

    usage_counter &operator++() { ++value; return *this; }
    usage_counter &operator--() { --value; return *this; }
};

#endif // USAGE_COUNTER_H
