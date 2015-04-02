#include "chunked_test_resource.h"

#include <iostream>

using namespace std;

ssize_t response_cycle_callback(const string &buf)
{
    static bool first_time = true;

    cout << "Callback called with buffer: [" << buf << "]" << endl;

    if (first_time)
    {
        const_cast<string &>(buf) = "5\r\ntest2\r\n";
        first_time = false;

        return sizeof("5\r\ntest2\r\n");
    }
    else
    {
        return -1;
    }
}

void chunked_test_resource::render_GET(const http_request &req,
                                       http_response **res)
{
    cout << "chunked_test_resource: GET called" << endl;

    *res = new http_response(http_response_builder("test")
                             .with_header("Transfer-Encoding", "chunked")
                             .deferred_response(response_cycle_callback));
}
