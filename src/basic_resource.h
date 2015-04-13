#ifndef BASIC_RESOURCE_H
#define BASIC_RESOURCE_H

#include <httpserver.hpp>


// Base for HTTP resources
class basic_resource
{
protected:
    httpserver::http_response *make_error_response(const std::string &msg,
                                                   int status_code);
};

#endif // BASIC_RESOURCE_H
