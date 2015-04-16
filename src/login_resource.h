#ifndef LOGIN_RESOURCE_H
#define LOGIN_RESOURCE_H

#include <httpserver.hpp>

#include "basic_resource.h"


class login_resource
    : public basic_resource,
      public httpserver::http_resource<login_resource>
{
    httpserver::http_response *make_GET_response(
        const httpserver::http_request &);

    httpserver::http_response *make_auth_fail_response(
        const std::string &msg,
        const std::string &username);

public:
    void render_GET(const httpserver::http_request &,
                    httpserver::http_response **);
};

#endif // LOGIN_RESOURCE_H
