#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "config.h"


enum status_code : int
{
    bad_request = 400,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
};

void start_http_server();

#endif // HTTP_SERVER_H
