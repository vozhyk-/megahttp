#ifndef FILE_CACHE_ITEM_H
#define FILE_CACHE_ITEM_H

#include <memory>

#include "mega_client.h"
#include "streaming_listener.h"


class file_cache_item
{
    friend class streaming_listener;

    mega::MegaApi &mega_api;

    std::vector<char> buffer;

    streaming_listener mega_transfer_listener;

    void start_download();
    void start_download(size_t start, size_t size);

public:
    using node_ptr = std::unique_ptr<mega::MegaNode>;

    // takes node away (move)
    file_cache_item(node_ptr node, mega::MegaApi &api);

    node_ptr node;
    int64_t full_size;
    bool downloading;

    void append_data(char *data, size_t size);
    ssize_t get_chunk(size_t start, size_t max_size, char *&result);
};

#endif // FILE_CACHE_ITEM_H
