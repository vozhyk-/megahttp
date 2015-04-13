#include "login_resource.h"

#include "http_server.h"
#include "logging.h"
#include "text.h"

using namespace std;
using namespace httpserver;
using namespace logging;


void login_resource::render_GET(const http_request &req, http_response **res)
{
    vector<string> path = req.get_path_pieces();

    // Log request path
    const auto t = msg_type::login_request_path;
    if (logger.will_log(t))
    {
        auto &log = logger.log(t);
        for (auto &s : path)
            log << s << "/";
        log << endl;
    }

    log_headers(req);

    // Check path
    if (path.size() < 2) // No email specified
    {
        *res = make_error_response(response_msg::path_email_not_specified,
                                   status_code::bad_request);
        return;
    }

    string username = path.back();
    string password = req.get_pass();

    // Check password presence
    if (password.empty())
    {
        *res = new http_response(
            http_response_builder("Authenticate")
            .basic_auth_fail_response("MEGA account"));
        return;
    }

    *res = make_error_response("Not implemented.",
                               status_code::not_implemented);
}
