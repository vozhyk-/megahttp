#include "file_buffer.h"

#include <cassert>
#include <cstring>
#include <iostream>

#include "file_cache.h"

using namespace std;

using namespace logging;


/*!
 * @param cache The whole cache for reserving memory in it
 */
file_buffer::file_buffer(int64_t full_size, class file_cache &cache)
    : cache{cache}, full_size{full_size}
{
}

file_buffer::~file_buffer()
{
}

/*!
 * Returns pointer to the block_num'th block if it exists,
 * otherwise creates the block first
 * (with given size)
 */
file_buffer::block_ptr &file_buffer::get_block(int block_num, size_t size)
{
    unique_lock<mutex> lock{blocks_mutex};
    auto found = blocks.find(block_num);

    if (found != blocks.end())
    {
        // logger.log(msg_type::file_buffer_blocks)
        //     << "found block " << &found->second
        //     << endl;
        return found->second;
    }
    else
    {
        auto i = blocks.insert(make_pair(block_num,
                                         block_ptr{new block{size, *this}}));
        // logger.log(msg_type::file_buffer_blocks)
        //     << "created block " << &i.first->second
        //     << endl;
        return i.first->second;
    }
}

/*!
 * Loops over blocks corresponding to
 * buffer[buffer_pos .. buffer_pos + data_size) ,
 * providing (block_ptr &bl // pointer to current buffer block,
 *            char *data // pointer to remaining data,
 *            size_t bl_pos // current position inside block,
 *            size_t to_copy // number of bytes remaining inside block
 *                           // (block[bl_pos .. bl_pos + to_copy) )
 * to the given function.
 * @param fun must be a function-like object with signature:
 * void fun(block_ptr &bl, char *data, size_t bl_pos, size_t to_copy);
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
        // logger.log(msg_type::file_buffer_blocks)
        //      << "with_blocks:"
        //      << " full size " << full_size
        //      << " buffer pos " << buffer_pos
        //      << " block size " << block_size
        //      << " data " << (void *)data
        //      << endl;
        size_t bl_size = min(block_size, full_size - bl_num*block_size);

        block_ptr &bl = get_block(bl_num, bl_size);
        size_t to_copy = min(data_size, bl_size - bl_pos);

        logger.log(msg_type::file_buffer_blocks)
            << "with_blocks:"
            << " bl_num " << bl_num
            << " bl " << bl.get()
            << " bl_pos " << bl_pos
            << " bl_size " << bl_size
            << " data " << (void *)data
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
    logger.log(msg_type::file_buffer_blocks)
        << "get_data"
        // << ": current_size " << current_size
        << endl;
    ssize_t data_to_copy = min(max_size, current_size - start);

    with_blocks(dest, data_to_copy, start,
                [] (block_ptr &bl, char *dest, size_t bl_pos, size_t to_copy)
    {
        // logger.log(msg_type::file_buffer_blocks)
        //     << "get_data:"
        //     << " bl->size() " << bl->size()
        //     << endl;
        memcpy(dest, bl->data() + bl_pos, to_copy);
        assert(!memcmp(dest, bl->data() + bl_pos, to_copy));
    });

    return data_to_copy;
}

void file_buffer::append_data(char *data, size_t size)
{
    logger.log(msg_type::file_buffer_blocks)
        << "append_data" << endl;
    with_blocks(data, size, current_size,
                [] (block_ptr &bl, char *data, size_t bl_pos, size_t to_copy)
    {
        // logger.log(msg_type::file_buffer_blocks)
        //     << "append_data: bl->size() before = " << bl->size()
        //     << endl;

        bl->insert(bl->end(), data, data + to_copy);

        // logger.log(msg_type::file_buffer_blocks)
        //     << "append_data: bl->size() after = " << bl->size()
        //     << endl;
        assert(!memcmp(data, bl->data() + bl_pos, to_copy));
    });

    current_size += size;
}

size_t file_buffer::mem_used()
{
    size_t result = 0;

    for (auto i = blocks.begin(); i != blocks.end(); ++i)
        result += i->second->mem_used();

    return result;
}

file_buffer::block::block(size_t bl_size, file_buffer &parent)
    : parent{parent}
{
    /*
     * TODO ensure nobody else does the same at this time.
     *      Allow only one block at a time to reserve memory?
     */
    parent.cache.ensure_free(bl_size);

    reserve(bl_size);

    parent.cache.buf_mem_used += mem_used();
}

file_buffer::block::~block()
{
    parent.cache.buf_mem_used -= mem_used();
}
