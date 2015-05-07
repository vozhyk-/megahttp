#include "file_cache_item.h"

using namespace std;
using namespace mega;


file_cache_item::file_cache_item(unique_ptr<MegaNode> node,
                                 MegaApi &api,
                                 class file_cache &cache)
    : mega_api{api}, cache{cache}, node{move(node)},
      full_size{this->node->getSize()},
      downloading(false), download_listener(*this)
{
    /*
     * TODO ensure nobody else does the same at this time.
     *      Allow only one file_cache_item at a time to reserve memory?
     */
    cache.ensure_free(full_size);

    buffer.reserve(full_size);
    cache.buf_mem_used += full_size;
}

file_cache_item::~file_cache_item()
{
    // TODO Stop download
    cache.buf_mem_used -= full_size;
}

void file_cache_item::start_download()
{
    start_download(0, full_size);
}

void file_cache_item::start_download(size_t start, size_t size)
{
    mega_api.startStreaming(node.get(), start, size, &download_listener);
    downloading = true;
}

void file_cache_item::append_data(char *data, size_t size)
{
    buffer.insert(buffer.end(), data, data + size);

    download_cond.notify_all();
}

void file_cache_item::update_last_used()
{
    // TODO use locking
    last_used = interval_clock::now();
}

ssize_t file_cache_item::get_chunk_immediately(size_t start,
                                               size_t max_size,
                                               char *&result)
{
    if (start >= buffer.size())
    {
        result = nullptr;

        if (start >= full_size)
        {
            // end-of-stream
            return -1;
        }
        else
        {
            // not downloaded yet
            if (!downloading)
                start_download();
            return 0;
        }
    }

    return get_buffer_chunk(start, max_size, result);
}

ssize_t file_cache_item::get_chunk(size_t start,
                                   size_t max_size,
                                   char *&result)
{
    ssize_t size;
    while (!(size = get_chunk_immediately(start, max_size, result)))
        wait_for_download();

    return size;
}

void file_cache_item::wait_for_download()
{
    unique_lock<mutex> lock{download_cond_mutex};
    download_cond.wait(lock);
}

ssize_t file_cache_item::get_buffer_chunk(size_t start,
                                          size_t max_size,
                                          char *&result)
{
    result = buffer.data() + start;

    return min(max_size, buffer.size() - start);
}

size_t file_cache_item::mem_used()
{
    return buffer.capacity();
}

size_t file_cache_item::have_bytes()
{
    return buffer.size();
}
