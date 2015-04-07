#include "megahttp_resource.h"

#include "config.h"

#include <iostream>
#include <memory>
#include <thread>

#include "mega_client.h"
#include "file_cache.h"

using namespace std;
using namespace httpserver;
using namespace mega;

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

ssize_t response_callback(char *out_buf, size_t max_size)
{
    thread_local static size_t file_offset = 0;

    char *data;
    ssize_t to_copy = cached->get_chunk(file_offset, max_size, data);

    cout << "HTTP data requested: file_offset " << file_offset
         << ", max_size " << max_size
         << ", to_copy " << to_copy
         << ", data " << (void *)data
         << ", filename ``" << cached->node->getName() << "''"
         << endl;

    if (to_copy > 0) // we got data
    {
        memcpy(out_buf, data, to_copy);
        file_offset += to_copy;
    }
    else if (to_copy == 0)
    {
        this_thread::sleep_for(http_response_sleep);
    }

    return to_copy;
};

void megahttp_resource::render_GET(const http_request &req, http_response **res)
{
    string mega_url = req.get_arg("url");
    // TODO check mega_url

    cout << "url: " << mega_url << endl;

    cout << "==== Headers:" << endl;

    map<string, string, header_comparator> headers;
    req.get_headers(headers);
    for (auto i : headers)
        cout << i.first << ": " << i.second << endl;

    // TODO use exceptions to handle errors

    // get node
    shared_ptr<MegaNode> node(get_mega_public_node(mega_url));

    cout << "file size: " << node->getSize() << endl;

    /* start node download */
    cached = file_cache[node]; // must set this for callback to work

    // TODO look at HTTP request range !

    // associate http callback with http response
    *res = new http_response(http_response_builder("")
                             .deferred_response(response_callback));
}
