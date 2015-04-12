#ifndef MEGAHTTP_RESORUCE_H
#define MEGAHTTP_RESORUCE_H

#include <httpserver.hpp>


class megahttp_resource
    : public httpserver::http_resource<megahttp_resource>
{
public:
    void render_GET(const httpserver::http_request &,
                    httpserver::http_response **);
};

#endif // MEGAHTTP_RESORUCE_H
