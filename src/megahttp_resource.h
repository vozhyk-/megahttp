#ifndef MEGAHTTP_RESORUCE_H
#define MEGAHTTP_RESORUCE_H

#include <httpserver.hpp>

using namespace httpserver;

class megahttp_resource : public http_resource<megahttp_resource>
{
public:
    void render_GET(const http_request &, http_response **);
};

#endif // MEGAHTTP_RESORUCE_H
