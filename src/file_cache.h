#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include <megaapi.h>
#include <unordered_map>
#include <memory>

#include "file_cache_item.h"


class file_cache
{
public:
    file_cache_item &operator()(std::unique_ptr<mega::MegaNode>,
                                mega::MegaApi &);

    size_t mem_used();

    using item_type = std::unique_ptr<file_cache_item>;
    using map_elem_type = std::pair<const mega::MegaHandle,
                                    item_type>;

    std::unordered_map<mega::MegaHandle, item_type> items;
};

extern file_cache file_cache;

#endif // FILE_CACHE_H
