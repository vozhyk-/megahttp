#ifndef CHUNKED_TEST_RESOURCE_H
#define CHUNKED_TEST_RESOURCE_H

#include <httpserver.hpp>

using namespace httpserver;

class chunked_test_resource : public http_resource<chunked_test_resource>
{
public:
    void render_GET(const http_request &, http_response **);
};

#endif // CHUNKED_TEST_RESOURCE_H
