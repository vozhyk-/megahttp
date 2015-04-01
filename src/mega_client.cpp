#include "mega_client.h"

#include "get_public_node_listener.h"
#include "transfer_listener.h"

using namespace std;
using namespace mega;


const char *APP_KEY = "HUc2iQaJ";

MegaApi *mega_api;

void init_mega()
{
    // TODO investigate enabling local caching
    mega_api = new MegaApi(APP_KEY);

    mega_api->setLogLevel(MegaApi::LOG_LEVEL_INFO);
}

MegaNode *get_mega_public_node(string url)
{
    get_public_node_listener listener;

    mega_api->getPublicNode(url.c_str(), &listener);
    return listener.wait_for_result();
}

string download_public_file_to_tmp(string url)
{
    MegaNode *node = get_mega_public_node(url);

    /* Create a path to download to */
    // TODO make the filename look better
    string local_path = "/tmp/" + to_string(node->getHandle());

    /* Download the file */
    transfer_listener t_listener;
    mega_api->startDownload(node, local_path.c_str(), &t_listener);
    bool successful = t_listener.wait_for_result();
}
