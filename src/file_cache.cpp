#include "file_cache.h"

class file_cache file_cache;

file_cache::value_type &file_cache::operator[](shared_ptr<MegaNode> node)
{
    MegaHandle handle = node->getHandle();
    auto found = items.find(handle);

    if (found != items.end()) // key present
        return found->second;
    else
        // create new cache_item
        return items[handle] = value_type(new file_cache_item(node));
}