#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

// for int types
#include <megaapi.h>
#include <unordered_map>
#include <memory>
#include <mutex>

#include "config.h"


class file_cache;

class file_buffer
{
    struct block : public std::vector<char>
    {
        /*!
         * Makes a block of size bl_size
         *
         * (bl_size later accessed by .capacity()
         *  - .size() returns how much it is filled instead
         */
        block(size_t bl_size, file_buffer &parent);
        ~block();

        block(const block &) = delete;
        block &operator=(const block &) = delete;

        size_t mem_used() { return capacity(); }

        file_buffer &parent;
    };

    using block_ptr = std::unique_ptr<block>;

    std::unordered_map<int, block_ptr> blocks;

    std::mutex blocks_mutex;
    block_ptr &get_block(int block_num, size_t block_size);

    template<typename function>
    void with_blocks(char *data, size_t data_size, size_t buffer_pos,
                     function fun);

    class file_cache &cache;

    int64_t current_size{0};
    int64_t full_size;

public:
    file_buffer(int64_t full_size, class file_cache &cache);
    ~file_buffer();

    size_t size() { return current_size; }
    size_t mem_used();

    ssize_t get_data(size_t start, size_t max_size, char *dest);
    // TODO replace with put_chunk
    void append_data(char *data, size_t size);
};

#endif // FILE_BUFFER_H
