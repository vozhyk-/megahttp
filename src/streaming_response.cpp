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
    ssize_t size = cached.get_data(file_offset, max_size, out_buf);

    logger.log(msg_type::response_data)
        << id
        << "file_offset " << file_offset
        << ", max_size " << max_size
        << ", size " << size
        << endl;

    if (size == -1) // end of stream
        logger.log(msg_type::response_status)
            << id
            << "finished." << endl;
    else // we got data
        file_offset += size;

    return size;
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
