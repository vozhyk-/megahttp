#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "config.h"


enum status_code : int
{
    internal_server_error = 500,
};

void start_http_server();

#endif // HTTP_SERVER_H
