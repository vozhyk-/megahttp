#include "login_resource.h"

#include "http_server.h"
#include "mega_client.h"
#include "logging.h"
#include "logging_utils.h"
#include "text.h"

using namespace std;
using namespace httpserver;

using namespace logging;


http_response *login_resource::make_GET_response(const http_request &req)
{
    vector<string> path = req.get_path_pieces();

    log_path(path);
    log_headers(req);

    // Check path
    if (path.size() < 2) // No email specified
        return make_msg_response(response_msg::path_email_not_specified,
                                 status_code::bad_request);

    string username = path.back();

    // Check if user already logged in
    if (mega_accounts[username])
    {
        return make_msg_response(response_msg::already_logged_in,
                                 status_code::ok);
    }
    else
    {
        string password = req.get_pass();

        // Check password presence
        if (password.empty())
        {
            // TODO log
            return make_auth_fail_response(response_msg::log_in,
                                           username);
        }

        // Try to log in
        try
        {
            add_account(username, password);
        }
        catch (mega_account::invalid_credentials)
        {
            return make_auth_fail_response(response_msg::invalid_credentials,
                                           username);
        }
        catch (const mega_account::other_login_error &e)
        {
            return make_msg_response(
                response_msg::mega_login_failed
                + e.error->getErrorString() + ".",
                status_code::internal_server_error);
        }

        return make_msg_response(
            response_msg::mega_login_successful,
            status_code::ok);
    }
}

http_response *login_resource::make_auth_fail_response(const string &msg,
                                                       const string &username)
{
    logger.log(msg_type::response_msg) << msg << endl;

    return new http_response(http_response_builder(msg + '\n')
                             .basic_auth_fail_response(username));
}

void login_resource::render_GET(const http_request &req, http_response **res)
{
    *res = make_GET_response(req);
}
