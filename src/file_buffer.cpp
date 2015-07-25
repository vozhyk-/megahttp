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

ssize_t file_buffer::get_chunk(size_t start,
                                   size_t max_size,
                                   char *&result)
{
    result = buffer.data() + start;

    return min(max_size, buffer.size() - start);
}


void file_buffer::append_data(char *data, size_t size)
{
    buffer.insert(buffer.end(), data, data + size);
}
