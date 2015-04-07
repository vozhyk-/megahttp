#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include <megaapi.h>
#include <unordered_map>
#include <memory>

#include "file_cache_item.h"

using namespace std;
using namespace mega;

class file_cache
{
    using value_type = shared_ptr<file_cache_item>;
    unordered_map<MegaHandle, value_type> items;

public:
    value_type &operator[](shared_ptr<MegaNode>);
};

extern file_cache file_cache;

#endif // FILE_CACHE_H
