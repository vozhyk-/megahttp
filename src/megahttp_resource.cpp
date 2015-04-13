#include "megahttp_resource.h"

#include "config.h"

#include <iostream>
#include <memory>
#include <thread>

#include "logging.h"
#include "text.h"
#include "http_server.h"

using namespace std;
using namespace httpserver;
using namespace mega;

using namespace logging;


void megahttp_resource::render_GET(const http_request &req, http_response **res)
{
    string mega_url = req.get_arg("url");

    // Log request info
    const auto t = msg_type::request_info;
    if (logger.will_log(t))
    {
        logger.log(t) << "url: " << mega_url << endl;

        logger.log(t) << "Headers:" << endl;

        map<string, string, header_comparator> headers;
        req.get_headers(headers);
        for (auto i : headers)
            logger.log(t)
                << "  " << i.first << ": " << i.second << endl;
    }

    // Check mega_url
    if (mega_url.empty())
    {
        *res = make_error_response(response_msg::empty_url,
                                   status_code::bad_request);
        return;
    }
    // TODO Further check mega_url — correctness of format, presence of key

    // Get node
    shared_ptr<MegaNode> node;
    auto error = get_mega_public_node(mega_url, node);

    switch (error->getErrorCode())
    {
    case MegaError::API_OK:
    {
        string id = node_id(node);
        logger.log(msg_type::file_info)
            << id << "file name: " << node->getName()
            << endl;
        logger.log(msg_type::file_info)
            << id << "file size: " << node->getSize()
            << endl;

        // TODO look at HTTP request range !
        auto *cb = new response_callback(node);

        // associate http callback with http response
        *res = new http_response(http_response_builder("")
                                 .deferred_response(cb));
        return;
    }

    case MegaError::API_ENOENT: // Not found
    {
        *res = make_error_response(response_msg::node_not_found,
                                   status_code::not_found);
        return;
    }

    default:
    {
        *res = make_error_response(
            response_msg::failed_to_get_node + error->getErrorString() + ".",
            status_code::internal_server_error);
    }
    }
}

http_response *megahttp_resource::make_error_response(const string &msg,
                                                      int status_code)
{
    logger.log(msg_type::response_error)
        << msg << endl;

    return new http_response(http_response_builder(msg + '\n', status_code)
                             .string_response());
}

ssize_t response_callback::operator()(char *out_buf, size_t max_size)
{
    char *data;
    ssize_t to_copy = cached->get_chunk(file_offset, max_size, data);

    logger.log(msg_type::response_data)
        << id
        << "file_offset " << file_offset
        << ", max_size " << max_size
        << ", to_copy " << to_copy
        << ", data " << (void *)data
        << endl;

    if (to_copy > 0) // we got data
    {
        memcpy(out_buf, data, to_copy);
        file_offset += to_copy;
    }
    else if (to_copy == 0) // data not available yet
    {
        this_thread::sleep_for(http_response_sleep);
    }
    else if (to_copy == -1) // end of stream
    {
        logger.log(msg_type::response_status)
            << id
            << "finished." << endl;
    }

    return to_copy;
};
