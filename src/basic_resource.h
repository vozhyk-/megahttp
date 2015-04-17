#ifndef BASIC_RESOURCE_H
#define BASIC_RESOURCE_H

#include <httpserver.hpp>


// Base for HTTP resources
class basic_resource
{
protected:
    httpserver::http_response *make_msg_response(const std::string &msg,
                                                 int status_code);

public:
    using str_iter = std::vector<std::string>::const_iterator;
    static std::string path_to_string(str_iter beg, str_iter end);
};

#endif // BASIC_RESOURCE_H
