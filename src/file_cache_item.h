#ifndef FILE_CACHE_ITEM_H
#define FILE_CACHE_ITEM_H

#include <memory>
#include <chrono>

#include "mega_client.h"
#include "streaming_listener.h"
#include "file_cache.h"
#include "usage_counter.h"


class file_cache;

class file_cache_item
{
    friend class streaming_listener;

    class file_cache &cache;

    mega::MegaApi &mega_api;

    std::vector<char> buffer;

    streaming_listener mega_transfer_listener;

    void start_download();
    void start_download(size_t start, size_t size);

public:
    using node_ptr = std::unique_ptr<mega::MegaNode>;
    using interval_clock = std::chrono::steady_clock;

    // takes node away (move)
    file_cache_item(node_ptr node, mega::MegaApi &, class file_cache &);

    ~file_cache_item();

    void append_data(char *data, size_t size);
    ssize_t get_chunk(size_t start, size_t max_size, char *&result);

    // Updates "last used" timestamp
    void update_last_used();

    node_ptr node;
    int64_t full_size;
    bool downloading;

    usage_counter in_use;
    interval_clock::time_point last_used; // TODO change value

    // Memory allocated for the buffer
    size_t mem_used();
    // How much of the file is in the cache
    size_t have_bytes();
};

#endif // FILE_CACHE_ITEM_H
