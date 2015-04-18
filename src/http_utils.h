#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include <httpserver.hpp>
#include <megaapi.h>


httpserver::http_response *make_msg_response(const std::string &msg,
                                             int status_code);

// str_iter not used anywhere else
using str_iter = std::vector<std::string>::const_iterator;
std::string path_to_string(str_iter beg, str_iter end);

#endif // HTTP_UTILS_H
