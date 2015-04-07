#include "megahttp_resource.h"

#include <iostream>

#include "mega_client.h"
#include "get_public_node_listener.h"
#include "file_cache.h"

using namespace std;
using namespace httpserver;
using namespace mega;

#define END_OF_STREAM -1;

/*
 * file_cache
 *  \- file_cache_item
 *      \- streaming_listener
 *
 * cache[file].mega_transfer_listener
 */

/*
class request
{
public:
    cache_item *cached;
    size_t file_offset;

    cycle_callback_ptr http_data_callback;
};
*/

thread_local shared_ptr<file_cache_item> cached;

void megahttp_resource::render_GET(const http_request &req, http_response **res)
{
    string mega_url = req.get_arg("url");
    // TODO check mega_url

    cout << "url: " << mega_url << endl;

    // TODO use exceptions to handle errors
    // TODO don't download every time - make a cache (class)

    // get node
    MegaNode *node = get_mega_public_node(mega_url);
    auto file_size = node->getSize();

    cout << "node size: " << file_size << endl;

    // start node download
    // TODO look at HTTP request range !
    cached = file_cache[node];
    auto *listener = &cached->mega_transfer_listener;

    mega_api->startStreaming(node, 0, file_size, listener);

    auto response_callback = [] (char *out_buf, size_t size) -> ssize_t
    {
        thread_local static size_t file_offset = 0;

        char *data;
        size_t to_copy = cached->get_chunk(file_offset, data);

        if (to_copy > 0)
            memcpy(out_buf, data, to_copy);

        return to_copy;
    };

    // associate http callback with http response
    *res = new http_response(http_response_builder("")
                             .deferred_response(response_callback));
}
