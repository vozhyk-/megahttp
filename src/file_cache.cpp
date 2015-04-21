#include "file_cache.h"

#include <numeric>
#include <set>

#include "logging_utils.h"

using namespace std;
using namespace mega;

using namespace logging;


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
            new file_cache_item{move(node), api, *this}};
        return *p;
    }
}

size_t file_cache::mem_used()
{
    return buf_mem_used;
}

bool file_cache::enough_free(size_t needed)
{
    return mem_limit - mem_used() < needed;
}

void file_cache::ensure_free(size_t needed)
{
    unique_lock<mutex> lock {gc_mutex};

    if (enough_free(needed))
        garbage_collect(needed);
}

void file_cache::garbage_collect(size_t needed)
{
    using map_iter = items_type::const_iterator;

    auto less_recently_used =
        [](map_iter x, map_iter y)
    {
        return x->second->last_used < y->second->last_used;
    };

    using fun_pointer = bool(*)(map_iter, map_iter);

    // Is going to hold items in least-recently-used-first order.
    // (Set of map_iter's with less_recently_used comparator)
    set<map_iter,
        decltype(static_cast<fun_pointer>(
                     less_recently_used))>
       queue;

    const auto t = msg_type::file_cache_gc;
    logger.log(t)
        << "started." << endl;

    logger.log(t) << items.size() << " items to check" << endl;

    // Put all items not in use into queue
    for (map_iter i = items.begin(); i != items.end(); ++i)
    {
        auto &item = i->second;
        if (!item->in_use)
            queue.insert(i);
        else
            logger.log(t)
                << node_id(*item->node) << "in use, will not remove." << endl;
    }

    size_t freed = 0;
    // Remove items from cache until (freed enough) or (end of queue)
    for (auto i : queue)
    {
        auto &item = i->second;
        size_t to_free {item->mem_used()};

        logger.log(t)
            << node_id(*item->node)
            << "freeing " << to_free << " bytes"
            << endl;

        items.erase(i);
        freed += to_free;
        if (enough_free(needed))
            return;
    }

    logger.log(t)
        << "freed " << freed << " bytes." << endl;
}
