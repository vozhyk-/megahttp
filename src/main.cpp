#include <httpserver.hpp>
#include "megahttp_resource.h"

using namespace std;
using namespace httpserver;

const int SERVER_PORT = 8080;

int main()
{
    webserver server = create_webserver(SERVER_PORT).max_threads(5);

    megahttp_resource resource;
    server.register_resource("/", &resource, true);

    server.start(true);
    return 0;
}
