#include "file_buffer.h"

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

ssize_t file_buffer::get_data(size_t start,
                              size_t max_size,
                              char *dest)
{
    // result = buffer.data() + start;

    // return min(max_size, buffer.size() - start);
    return 0;
}


void file_buffer::append_data(char *data, size_t size)
{
    size_t remaining = size;
    size_t buffer_pos = current_size;
    while (remaining > 0)
    {
        int bl_num = buffer_pos / block_size;
        size_t bl_size = min(block_size, full_size - buffer_pos);

        block bl = get_block(bl_num, bl_size);
        size_t to_copy = min(remaining, bl_size);

        bl.insert(bl.end(), data, data + to_copy);

        data += to_copy;
        buffer_pos += to_copy;
        remaining -= to_copy;
    }
}
