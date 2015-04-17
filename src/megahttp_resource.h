#ifndef MEGAHTTP_RESORUCE_H
#define MEGAHTTP_RESORUCE_H

#include <httpserver.hpp>

#include "basic_resource.h"
#include "mega_client.h"
#include "file_cache.h"
#include "logging_utils.h"


class megahttp_resource
    : public basic_resource,
      public httpserver::http_resource<megahttp_resource>
{
    httpserver::http_response *make_GET_response(
        const httpserver::http_request &);
public:
    void render_GET(const httpserver::http_request &,
                    httpserver::http_response **);
};

class response_callback : public httpserver::data_callback
{
    std::shared_ptr<file_cache_item> cached;
    size_t file_offset;
    std::string id;

public:
    response_callback(std::shared_ptr<mega::MegaNode> node)
        : cached{file_cache[node]}, file_offset{0}, id{logging::node_id(*node)}
    {
    }

    ssize_t operator()(char *out_buf, size_t max_size);

    ~response_callback() {}
};

#endif // MEGAHTTP_RESORUCE_H
