#include "megahttp_resource.h"

#include <memory>

#include "logging.h"
#include "text.h"
#include "http_server.h"
#include "http_utils.h"
#include "streaming_response.h"

using namespace std;
using namespace httpserver;
using namespace mega;

using namespace logging;


http_response *megahttp_resource::make_GET_response(const http_request &req)
{
    string mega_url = req.get_arg("url");

    // Log request info
    const auto t = msg_type::request_info;
    if (logger.will_log(t))
        logger.log(t) << "url: " << mega_url << endl;

    log_headers(req);

    // Check mega_url
    if (mega_url.empty())
        return make_msg_response(response_msg::empty_url,
                                 status_code::bad_request);
    // TODO Further check mega_url — correctness of format, presence of key

    // Get node
    unique_ptr<MegaNode> node;
    auto error = get_mega_public_node(mega_url, node);

    switch (error->getErrorCode())
    {
    case MegaError::API_OK:
    {
        return make_node_response(move(node), *mega_api);
    }

    case MegaError::API_ENOENT: // Not found
        return make_msg_response(response_msg::node_not_found,
                                 status_code::not_found);

    default:
        return make_msg_response(
            response_msg::failed_to_get_node + error->getErrorString() + ".",
            status_code::internal_server_error);
    }
}

void megahttp_resource::render_GET(const http_request &req, http_response **res)
{
    *res = make_GET_response(req);
}
