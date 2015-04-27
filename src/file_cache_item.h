#ifndef FILE_CACHE_ITEM_H
#define FILE_CACHE_ITEM_H

#include <memory>
#include <chrono>

#include "mega_client.h"
#include "download_listener.h"
#include "file_cache.h"
#include "usage_counter.h"


class file_cache;

class file_cache_item
{
    friend class download_listener;

    class file_cache &cache;

    mega::MegaApi &mega_api;

    std::vector<char> buffer;

    class download_listener download_listener;

    std::condition_variable download_cond;
    std::mutex download_cond_mutex;

    ssize_t get_chunk_immediately(size_t start, size_t max_size, char *&result);
    ssize_t get_buffer_chunk(size_t start, size_t max_size, char *&result);

    void start_download();
    void start_download(size_t start, size_t size);

    void wait_for_download();

public:
    using node_ptr = std::unique_ptr<mega::MegaNode>;
    using interval_clock = std::chrono::steady_clock;

    // takes node away (move)
    file_cache_item(node_ptr node, mega::MegaApi &, class file_cache &);

    ~file_cache_item();

    void append_data(char *data, size_t size);
    // Maybe returning a pair<ssize_t, char *> is a better idea?
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
