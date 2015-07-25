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
        // Add new cache_item
        using temp = pair<items_type::iterator, bool>;
        temp i = items.insert(make_pair(handle, item_type{
                    new file_cache_item{move(node), api, *this}}));
        // return newly added item
        return *i.first->second;
    }
}

size_t file_cache::mem_used()
{
    return buf_mem_used;
}

bool file_cache::enough_free(size_t needed)
{
    // low-level debug
    //
    // logger.log(msg_type::file_cache_gc)
    //     << "checking free: used " << mem_used()
    //     << " needed " << needed
    //     << " sum " << mem_used() + needed
    //     << " limit " << mem_limit
    //     << " comparison " << (mem_used() + needed <= mem_limit)
    //     << endl;

    // Using + so that there is no unsigned overflow
    return mem_used() + needed <= mem_limit;
}

void file_cache::ensure_free(size_t needed)
{
    unique_lock<mutex> lock {gc_mutex};

    if (!enough_free(needed))
        garbage_collect(needed);
    else
        logger.log(msg_type::file_cache_gc)
            << "enough memory in cache, not running gc." << endl;
}

void file_cache::garbage_collect(size_t needed)
{
    // using map_iter = items_type::const_iterator;

    // auto less_recently_used =
    //     [](map_iter x, map_iter y)
    // {
    //     auto &item_x = x->second;
    //     auto &item_y = y->second;
    //     /* <= used so that items with equal last_used
    //      * are placed into queue too
    //      */
    //     return item_x->last_used <= item_y->last_used;
    // };

    // // Is going to hold items in least-recently-used-first order.
    // // (Set of map_iter's with less_recently_used comparator)
    // set<map_iter, typeof(less_recently_used)> queue {less_recently_used};

    const auto t = msg_type::file_cache_gc;
    logger.log(t)
        << "started." << endl;

    // logger.log(t) << "checking " << items.size() << " items" << endl;

    // // Put all items not in use into queue
    // for (map_iter i = items.begin(); i != items.end(); ++i)
    // {
    //     auto &item = i->second;
    //     if (!item->in_use)
    //         queue.insert(i);
    //     else
    //         // TODO Add id member to cache_item?
    //         logger.log(t)
    //             << node_id(*item->node) << "in use, will not remove." << endl;
    // }

    // logger.log(t) << queue.size() << " items not in use, can be removed"
    //               << endl;

    // size_t freed = 0;
    // int count = 0;
    // // Remove items from cache until (freed enough) or (end of queue)
    // for (auto i : queue)
    // {
    //     auto &item = i->second;
    //     size_t to_free {item->mem_used()};

    //     logger.log(t)
    //         << "[" << count << "] " << node_id(*item->node)
    //         << "freeing " << to_free << " bytes"
    //         << endl;

    //     items.erase(i);
    //     freed += to_free;
    //     count++;
    //     if (enough_free(needed))
    //     {
    //         logger.log(t)
    //             << "freed enough memory." << endl;
    //         break;
    //     }
    // }

    // logger.log(t)
    //     << "removed " << count << " items,"
    //     << " freed " << freed << " bytes."
    //     << endl;
    logger.log(t)
        << "used now: " << mem_used() << endl;
}
