#include "login_resource.h"

#include "http_server.h"

using namespace std;
using namespace httpserver;


void login_resource::render_GET(const http_request &req, http_response **res)
{
    *res = new http_response(http_response_builder("Not implemented.",
                                                   status_code::not_implemented)
                             .string_response());
}
