#include "http_server.h"

#include <httpserver.hpp>

#include "megahttp_resource.h"
#include "chunked_test_resource.h"

using namespace std;
using namespace httpserver;

void start_http_server()
{
    webserver server = create_webserver(SERVER_PORT).max_threads(5);

    megahttp_resource resource;
    chunked_test_resource ct_resource;
    server.register_resource("/", &resource, true);
    server.register_resource("/chunked_test", &ct_resource, true);

    server.start(true);
}
