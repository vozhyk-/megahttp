#include "file_cache_item.h"

file_cache_item::file_cache_item(size_t full_size)
    : full_size(full_size), downloading(true), mega_transfer_listener(*this)
{
    buffer.reserve(full_size);
}

void file_cache_item::append_data(char *data, size_t size)
{
    buffer.insert(buffer.end(), data, data + size);
}

/*
 * Returns:
 *   the number of bytes available, or
 *    0, if the chunk is not downloaded yet,
 *   -1, if the chunk is past the end of file,
 *   -2, if the chunk couldn't be downloaded because of an error
 * Sets result to address of chunk if return value > 0
 */
size_t file_cache_item::get_chunk(size_t start, char *&result)
{
    if (start >= buffer.size())
    {
        if (start >= full_size)
        {
            // end-of-stream
            return -1;
        }
        else if (downloading)
        {
            // not downloaded yet
            return 0;
        }
        else // not downloading && chunk inside file
        {
            // error
            return -2;
        }
    }

    result = buffer.data() + start;

    return buffer.size() - start;
}
