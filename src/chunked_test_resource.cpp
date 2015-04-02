#include "chunked_test_resource.h"

#include <iostream>

using namespace std;

ssize_t response_cycle_callback(char *buf, size_t size)
{
    static int times = 0;

    cout << "Callback called " << times << "'th time"
         << " with size = " << size << endl;

    if (times >= 10)
        return -1;

    memset(buf, 'A' + times, 128);
    times++;
    /* Wait some time so that we actually see that chunking is happening */
    sleep(1);
    return 128;
}

void chunked_test_resource::render_GET(const http_request &req,
                                       http_response **res)
{
    cout << "chunked_test_resource: GET called" << endl;

    *res = new http_response(http_response_builder("test")
                             .deferred_response(response_cycle_callback));
}
