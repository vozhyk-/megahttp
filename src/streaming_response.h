#ifndef FILE_RESPONSE_H
#define FILE_RESPONSE_H

#include <httpserver.hpp>
#include <megaapi.h>

#include "logging_utils.h"
#include "file_cache.h"


httpserver::http_response *make_node_response(std::unique_ptr<mega::MegaNode>,
                                              mega::MegaApi &);

// used only here, can be moved to .cpp
class response_callback : public httpserver::data_callback
{
    file_cache_item &cached;
    size_t file_offset;
    std::string id;

public:
    using node_ptr = std::unique_ptr<mega::MegaNode>;
    response_callback(node_ptr node, mega::MegaApi &api)
        : file_offset{0},
          cached{file_cache(move(node), api)},
          id{logging::node_id(*cached.node)}
    {
        ++cached.in_use;
    }

    ~response_callback()
   {
       /* Updating only now because
        * last-used-time of items that are in use
        * is not considered by gc
        */
       cached.update_last_used();
       --cached.in_use;
   }

    ssize_t operator()(char *out_buf, size_t max_size);

};

#endif // FILE_RESPONSE_H
