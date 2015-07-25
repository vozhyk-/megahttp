#include "file_buffer.h"

#include <cstring>
#include <iostream>

#include "file_cache.h"

using namespace std;


/*!
 * @param cache The whole cache for reserving memory in it
 */
file_buffer::file_buffer(int64_t full_size, class file_cache &cache)
    : cache{cache}, full_size{full_size}
{
    /*
     * TODO ensure nobody else does the same at this time.
     *      Allow only one file_cache_item at a time to reserve memory?
     */
    cache.ensure_free(full_size);

    buffer.reserve(full_size);
    cache.buf_mem_used += full_size;
}

file_buffer::~file_buffer()
{
    cache.buf_mem_used -= full_size;
}

/*!
 * Returns the block_num'th block if it exists,
 * otherwise creates it first
 * (with given size)
 */
file_buffer::block &file_buffer::get_block(int block_num, size_t size)
{
    auto found = blocks.find(block_num);

    if (found != blocks.end())
    {
        return found->second;
    }
    else
    {
        auto i = blocks.insert(make_pair(block_num, block{size}));
        return i.first->second;
    }
}

/*!
 * Loops over blocks corresponding to
 * buffer[buffer_pos .. buffer_pos + data_size) ,
 * providing (block bl // current buffer block,
 *            char *data // pointer to remaining data,
 *            size_t bl_pos // current position inside block,
 *            size_t to_copy // number of bytes remaining inside block
 *                           // (block[bl_pos .. bl_pos + to_copy) )
 *
 * Used to copy data from or into buffer
 */
template<typename function>
void file_buffer::with_blocks(char *data, size_t data_size, size_t buffer_pos,
                              function fun)
{
    // data, data_size, buffer_pos will be modified on every iteration
    while (data_size > 0)
    {
        int    bl_num = buffer_pos / block_size;
        size_t bl_pos = buffer_pos % block_size;
        size_t bl_size = min(block_size, full_size - buffer_pos);

        block bl = get_block(bl_num, bl_size);
        size_t to_copy = min(data_size, bl_size);

        cout << "with_blocks:"
             << " bl_num " << bl_num
             << " bl_pos " << bl_pos
             << " bl_size " << bl_size
             << " to_copy " << to_copy
             << endl;

        fun(bl, data, bl_pos, to_copy);

        data += to_copy;
        buffer_pos += to_copy;
        data_size -= to_copy;
    }
}

ssize_t file_buffer::get_data(size_t start,
                              size_t max_size,
                              char *dest)
{
    ssize_t data_to_copy = min(max_size, current_size - start);

    with_blocks(dest, data_to_copy, start,
                [] (block bl, char *dest, size_t bl_pos, size_t to_copy)
    {
        memcpy(dest, bl.data() + bl_pos, to_copy);
    });

    return data_to_copy;
}


void file_buffer::append_data(char *data, size_t size)
{
    with_blocks(data, size, current_size,
                [] (block bl, char *data, size_t bl_pos, size_t to_copy)
    {
        bl.insert(bl.end(), data, data + to_copy);
    });
}
