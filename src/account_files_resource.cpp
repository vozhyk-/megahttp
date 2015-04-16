#include "account_files_resource.h"

using namespace httpserver;

http_response *account_files_resource::make_GET_response(
    const http_request &req)
{
    return nullptr; //stub
}

void account_files_resource::render_GET(const http_request &req,
                                        http_response **res)
{
    *res = make_GET_response(req);
}
