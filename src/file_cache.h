#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include <megaapi.h>
#include <unordered_map>
#include <memory>
#include <mutex>

#include "file_cache_item.h"
#include "config.h"


class file_cache
{
    friend class file_cache_item;

    std::mutex gc_mutex;

    size_t buf_mem_used {0};

    bool enough_free(size_t needed);

    void garbage_collect(size_t needed);

public:
    /*!
     * \brief Get an item for `node` from the cache
     *
     * Creates a new item if there isn't one already.
     */
    file_cache_item &operator()(std::unique_ptr<mega::MegaNode> node,
                                mega::MegaApi &);

    /// Memory used by file_cache_items' buffers
    size_t mem_used();
    /// Ensure mem_used is `needed` bytes below mem_limit
    // Change void to bool in the future?
    void ensure_free(size_t needed);

    using item_type = std::unique_ptr<file_cache_item>;
    using map_elem_type = std::pair<const mega::MegaHandle,
                                    item_type>;
    using items_type = std::unordered_map<mega::MegaHandle, item_type>;

    items_type items;
    size_t mem_limit = max_cache_size;
};

extern file_cache file_cache;

#endif // FILE_CACHE_H
