#include "file_cache.h"

using namespace std;
using namespace mega;


class file_cache file_cache;

file_cache_item &file_cache::operator()(unique_ptr<MegaNode> node,
                                        MegaApi &api)
{
    MegaHandle handle = node->getHandle();
    auto found = items.find(handle);

    if (found != items.end()) // key present
    {
        return *found->second;
    }
    else
    {
        // create new cache_item
        auto &p = items[handle] = item_type{
            new file_cache_item{move(node), api}};
        return *p;
    }
}
