#ifndef FILE_CACHE_ITEM_H
#define FILE_CACHE_ITEM_H

#include <memory>

#include "streaming_listener.h"


class file_cache_item
{
    friend class streaming_listener;

    std::vector<char> buffer;

    streaming_listener mega_transfer_listener;

    void start_download();
    void start_download(size_t start, size_t size);

public:
    file_cache_item(std::shared_ptr<mega::MegaNode> node);

    // we don't want us to be copied
    file_cache_item &operator=(file_cache_item &&) = default;

    std::shared_ptr<mega::MegaNode> node;
    size_t full_size;
    bool downloading;

    void append_data(char *data, size_t size);
    ssize_t get_chunk(size_t start, size_t max_size, char *&result);
};

#endif // FILE_CACHE_ITEM_H
