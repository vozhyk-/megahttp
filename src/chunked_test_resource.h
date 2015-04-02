#ifndef CHUNKED_TEST_RESOURCE_H
#define CHUNKED_TEST_RESOURCE_H

#include <httpserver.hpp>

using namespace httpserver;

class my_http_response_builder : public http_response_builder
{
    my_cycle_calback_ptr _my_cycle_callback;

public:
    http_response_builder &my_deferred_response(my_cycle_callback_ptr cb)
    {
        _my_cycle_callback = cb;
        _get_raw_response = &http_response::get_raw_response_deferred;
        _decorate_response = &http_response::decorate_response_deferred;
        return *this;
    }
};

class chunked_test_resource : public http_resource<chunked_test_resource>
{
    
public:
    void render_GET(const http_request &, http_response **);
};

#endif // CHUNKED_TEST_RESOURCE_H
