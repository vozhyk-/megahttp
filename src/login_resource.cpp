#include "login_resource.h"

#include "http_server.h"
#include "mega_client.h"
#include "logging.h"
#include "text.h"

using namespace std;
using namespace httpserver;
using namespace logging;


http_response *login_resource::make_GET_response(const http_request &req)
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
        return make_error_response(response_msg::path_email_not_specified,
                                   status_code::bad_request);
    }

    string username = path.back();
    string password = req.get_pass();

    // Check password presence
    if (password.empty())
    {
        // TODO log
        return new http_response(
            http_response_builder("Log in with MEGA email and password.")
            .basic_auth_fail_response("MEGA account"));
    }

    try
    {
        add_account(username, password);
    }
    catch (const mega_account::other_login_error &e)
    {
        return make_error_response(
            response_msg::mega_login_failed + e.error->getErrorString() + ".",
            status_code::internal_server_error);
    }

    return make_error_response("Not implemented.",
                               status_code::not_implemented);
}

void login_resource::render_GET(const http_request &req, http_response **res)
{
    *res = make_GET_response(req);
}
