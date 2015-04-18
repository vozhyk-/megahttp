#include "account_files_resource.h"

#include <megaapi.h>

#include "http_server.h"
#include "http_utils.h"
#include "streaming_response.h"
#include "mega_client.h"
#include "logging_utils.h"
#include "text.h"

using namespace std;
using namespace httpserver;
using namespace mega;

using namespace logging;

http_response *account_files_resource::make_GET_response(
    const http_request &req)
{
    /*
     * Example URL:
     *
     * http://server/email@example.com/some/file
     */

    vector<string> path = req.get_path_pieces();

    log_path(path);
    log_headers(req);

    // Check path
    if (path.size() < 2)
        return make_msg_response(response_msg::invalid_file_req_path,
                                 status_code::bad_request);

    string username = path.front();

    auto account = mega_accounts[username];

    if (!account)
        // For now just refuse to continue
        // TODO possibly allow to authenticate
        return make_msg_response(response_msg::not_logged_in,
                                 status_code::bad_request);

    string file_path = path_to_string(path.begin() + 1, path.end());

    // TODO fetchNodes must have been called previously for this to work
    unique_ptr<MegaNode> node{
        account->getNodeByPath(file_path.c_str()) };

    if (!node)
        return make_msg_response(response_msg::node_not_found,
                                 status_code::not_found);

    // TODO check if directory, if yes - fail

    return make_node_response(*node);
}

void account_files_resource::render_GET(const http_request &req,
                                        http_response **res)
{
    *res = make_GET_response(req);
}
