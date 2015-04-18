#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include <megaapi.h>
#include <unordered_map>
#include <memory>

#include "file_cache_item.h"


class file_cache
{
    using item_type = std::unique_ptr<file_cache_item>;
    std::unordered_map<mega::MegaHandle, item_type> items;

public:
    file_cache_item &operator()(std::unique_ptr<mega::MegaNode>,
                                mega::MegaApi &);
};

extern file_cache file_cache;

#endif // FILE_CACHE_H
