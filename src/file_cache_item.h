#ifndef FILE_CACHE_ITEM_H
#define FILE_CACHE_ITEM_H

#include "streaming_listener.h"

using namespace std;

class file_cache_item
{
public:
    file_cache_item(size_t full_size);

    // we don't want us to be copied
    file_cache_item &operator=(file_cache_item &&) = default;

    vector<char> buffer;
    size_t full_size;
    bool downloading;

    streaming_listener mega_transfer_listener;

    void append_data(char *data, size_t size);
    ssize_t get_chunk(size_t start, size_t max_size, char *&result);
};

#endif // FILE_CACHE_ITEM_H
