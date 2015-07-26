#ifndef FILE_CACHE_ITEM_H
#define FILE_CACHE_ITEM_H

#include <memory>
#include <chrono>

#include "mega_client.h"
#include "download_listener.h"
#include "file_cache.h"
#include "file_buffer.h"
#include "usage_counter.h"


class file_cache;

class file_cache_item
{
    friend class download_listener;

    mega::MegaApi &mega_api;

    std::unique_ptr<file_buffer> buffer;

    class download_listener download_listener;

    std::condition_variable download_cond;
    std::mutex download_cond_mutex;

    /*!
     * @return
     *   the number of bytes copied, or
     *    0, if the chunk is not downloaded yet,
     *   -1, if the chunk is past the end of file,
     *   -2, if the chunk couldn't be downloaded because of an error
     *       (NOT IMPLEMENTED)
     * Copies data into dest if return value > 0
     */
    ssize_t get_data_immediately(size_t start, size_t max_size, char *dest);

    void start_download();
    void start_download(size_t start, size_t size);

    void wait_for_download();

public:
    using node_ptr = std::unique_ptr<mega::MegaNode>;

    /// takes node away (move)
    file_cache_item(node_ptr node, mega::MegaApi &, class file_cache &);

    ~file_cache_item();

    void append_data(char *data, size_t size);
    /*!
     * Get a chunk of cached file.
     * Blocks, returns only when data available.
     *
     * @return The return value of get_chunk_immediately (but without 0).
     * Copies the chunk into dest.
     */
    ssize_t get_data(size_t start, size_t max_size, char *dest);

    node_ptr node;
    int64_t full_size;
    bool downloading;

    usage_counter in_use;

    /// Memory allocated for the buffer
    size_t mem_used();
    /// How much of the file is in the cache
    size_t have_bytes();
};

#endif // FILE_CACHE_ITEM_H
