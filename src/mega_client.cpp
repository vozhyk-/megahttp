#include "mega_client.h"

#include "get_public_node_listener.h"

using namespace std;
using namespace mega;


const char *APP_KEY = "HUc2iQaJ";

unique_ptr<MegaApi> mega_api;

void init_mega()
{
    // TODO investigate enabling local caching
    mega_api = unique_ptr<MegaApi>(new MegaApi(APP_KEY));

    mega_api->setLogLevel(MegaApi::LOG_LEVEL_INFO);
}

// @return string for identifying a node in log output
string node_id(shared_ptr<MegaNode> node)
{
    return "(" + string(node->getBase64Handle()) + ") ";
}

shared_ptr<MegaError> get_mega_public_node(string url,
                                           shared_ptr<MegaNode> &result)
{
    get_public_node_listener listener;

    mega_api->getPublicNode(url.c_str(), &listener);
    result = listener.wait_for_result();

    return listener.error;
}
