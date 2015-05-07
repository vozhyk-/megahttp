#include "streaming_response.h"

#include <thread>

#include "config.h"
#include "logging.h"

using namespace std;
using namespace httpserver;
using namespace mega;

using namespace logging;


ssize_t response_callback::operator()(char *out_buf, size_t max_size)
{
    char *data;
    ssize_t to_copy = cached.get_chunk(file_offset, max_size, data);

    logger.log(msg_type::response_data)
        << id
        << "file_offset " << file_offset
        << ", max_size " << max_size
        << ", to_copy " << to_copy
        << ", data " << (void *)data
        << endl;

    if (to_copy == -1) // end of stream
    {
        logger.log(msg_type::response_status)
            << id
            << "finished." << endl;
    }
    else // we got data
    {
        memcpy(out_buf, data, to_copy);
        file_offset += to_copy;
    }

    return to_copy;
};

http_response *make_node_response(unique_ptr<MegaNode> node, MegaApi &api)
{
    log_node(*node);

    // TODO look at HTTP request range !

    /*!
     * Node path:
     *   response_callback{}
     *   \- file_cache()
     *      |- (destroyed)
     *      \- file_cache_item{}
     *         \- (stored)
     */
    auto *cb = new response_callback{move(node), api};

    // associate http callback with http response
    return new http_response(http_response_builder("")
                             .deferred_response(cb));
}
