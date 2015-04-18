#ifndef MEGAHTTP_RESORUCE_H
#define MEGAHTTP_RESORUCE_H

#include <httpserver.hpp>

#include "mega_client.h"


class public_files_resource
    : public httpserver::http_resource<public_files_resource>
{
    httpserver::http_response *make_GET_response(
        const httpserver::http_request &);
public:
    void render_GET(const httpserver::http_request &,
                    httpserver::http_response **);
};

#endif // MEGAHTTP_RESORUCE_H
