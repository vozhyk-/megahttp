#include "status_resource.h"

#include "http_server.h"
#include "http_utils.h"
#include "logging_utils.h"

using namespace std;
using namespace httpserver;

using namespace logging;


http_response *status_resource::make_GET_response(const http_request &req)
{
    log_headers(req);

    return make_msg_response("Not implemented.",
                             status_code::not_implemented);
}

void status_resource::render_GET(const http_request &req,
                                 http_response **res)
{
    *res = make_GET_response(req);
}
