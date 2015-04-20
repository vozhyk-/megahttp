#ifndef STATUS_RESOURCE_H
#define STATUS_RESOURCE_H

#include <httpserver.hpp>


class status_resource
    : public httpserver::http_resource<status_resource>
{
    httpserver::http_response *make_GET_response(
        const httpserver::http_request &);
public:
    void render_GET(const httpserver::http_request &,
                    httpserver::http_response **);
};

#endif // STATUS_RESOURCE_H
