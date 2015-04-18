#include "mega_account.h"

#include "mega_client.h"

using namespace std;
using namespace mega;


mega_account::mega_account(const string &username,
                           const string &password)
    : MegaApi(app_key)
{
    error_listener listener;
    login(username.c_str(), password.c_str(), &listener);

    shared_ptr<MegaError> error = listener.wait_for_result();

    switch (error->getErrorCode())
    {
    case MegaError::API_ENOENT: // email/password invalid
    case MegaError::API_EARGS:  // Invalid argument
        // We don't make a distinction, maybe we should?
        throw invalid_credentials{};

    case MegaError::API_OK:
        fetch_nodes_start();
        return;

    default:
        throw other_login_error{error};
    }
}

void mega_account::fetch_nodes_start()
{
    fetchNodes(&fetch_nodes_listener);
}

unique_ptr<MegaNode> mega_account::get_node_by_path(string path)
{
    // TODO check returned error
    fetch_nodes_listener.wait_for_result();
    // TODO log error

    return unique_ptr<MegaNode>{ getNodeByPath(path.c_str()) };
}

void mega_account::error_listener::onRequestFinish(MegaApi *,
                                                   MegaRequest *,
                                                   MegaError *error)
{
    result = shared_ptr<MegaError>(new MegaError(*error));
    done = true;
}
