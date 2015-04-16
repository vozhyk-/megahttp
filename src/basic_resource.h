#ifndef BASIC_RESOURCE_H
#define BASIC_RESOURCE_H

#include <httpserver.hpp>


// Base for HTTP resources
class basic_resource
{
protected:
    httpserver::http_response *make_msg_response(const std::string &msg,
                                                 int status_code);
    void log_headers(const httpserver::http_request &req);
    void log_path(const std::vector<std::string> &path);
};

#endif // BASIC_RESOURCE_H
