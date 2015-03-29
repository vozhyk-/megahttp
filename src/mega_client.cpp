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

void download_public_file(string url, string local_path)
{
    /* Get the node from the URL */
    get_public_node_listener r_listener;
    mega_api->getPublicNode(url.c_str(), &r_listener);
    MegaNode *node = r_listener.wait_for_result();

    /* Download the file */
    transfer_listener t_listener;
    mega_api->startDownload(node, local_path.c_str(), &t_listener);
    bool successful = t_listener.wait_for_result();
}
