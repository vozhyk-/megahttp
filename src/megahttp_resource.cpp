#include "megahttp_resource.h"

#include "config.h"

#include <iostream>
#include <memory>
#include <thread>

#include "logging.h"
#include "text.h"
#include "http_server.h"
#include "mega_client.h"
#include "file_cache.h"

using namespace std;
using namespace httpserver;
using namespace mega;

using namespace logging;


class response_callback : public data_callback
{
    shared_ptr<file_cache_item> cached;
    size_t file_offset;
    string id;

public:
    response_callback(shared_ptr<MegaNode> node)
        : cached{file_cache[node]}, file_offset{0}, id{node_id(node)}
    {
    }

    ssize_t operator()(char *out_buf, size_t max_size)
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
        else if (to_copy == 0)
        {
            this_thread::sleep_for(http_response_sleep);
        }

        return to_copy;
    };

    ~response_callback() {}
};

void megahttp_resource::render_GET(const http_request &req, http_response **res)
{
    string mega_url = req.get_arg("url");
    // TODO check mega_url

    const auto t = msg_type::request_info;
    if (logger.will_log(t))
    {
        logger.log(t) << "url: " << mega_url << endl;

        logger.log(t) << "==== Headers:" << endl;

        map<string, string, header_comparator> headers;
        req.get_headers(headers);
        for (auto i : headers)
            logger.log(t) << i.first << ": " << i.second << endl;
    }

    // TODO use exceptions to handle errors

    // get node
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
    default:
    {
        string text =
            response_msg::get_node_fail + error->getErrorString();
        logger.log(msg_type::response_error)
            << text << endl;

        *res = new http_response(
            http_response_builder(text + '\n',
                                  status_code::internal_server_error)
            .string_response());
    }
    }
}
