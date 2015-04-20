#include "http_server.h"

#include <httpserver.hpp>

#include "public_files_resource.h"
#include "account_files_resource.h"
#include "login_resource.h"
#include "status_resource.h"

using namespace std;
using namespace httpserver;


void start_http_server()
{
    webserver server =
        create_webserver(server_port).max_threads(server_max_threads);

    account_files_resource a_resource;
    public_files_resource p_resource;
    login_resource l_resource;
    status_resource s_resource;
    server.register_resource("/", &a_resource, true);
    server.register_resource("/public", &p_resource, false);
    server.register_resource("/login", &l_resource, true);
    server.register_resource("/status", &s_resource, false);

    server.start(true);
}
