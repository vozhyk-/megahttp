#include "http_server.h"

#include <httpserver.hpp>

#include "megahttp_resource.h"

using namespace std;
using namespace httpserver;

void start_http_server()
{
    webserver server = create_webserver(SERVER_PORT).max_threads(5);

    megahttp_resource resource;
    server.register_resource("/", &resource, true);

    server.start(true);
}
