#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include <httpserver.hpp>
#include <megaapi.h>

namespace logging
{
    std::string node_id(mega::MegaNode &node);

    void log_headers(const httpserver::http_request &req);
    void log_path(const std::vector<std::string> &path);
    void log_node(mega::MegaNode &node);
}

#endif // LOG_UTILS_H
