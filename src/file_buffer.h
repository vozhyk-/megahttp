#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

// for int types
#include <megaapi.h>


class file_cache;

class file_buffer
{
    std::vector<char> buffer;

    class file_cache &cache;

    int64_t full_size;

public:
    file_buffer(int64_t full_size, class file_cache &cache);
    ~file_buffer();

    size_t size() { return buffer.size(); }
    size_t mem_used() { return buffer.capacity(); }

    ssize_t get_chunk(size_t start, size_t max_size, char *&result);
    // TODO replace with put_chunk
    void append_data(char *data, size_t size);
};

#endif // FILE_BUFFER_H
