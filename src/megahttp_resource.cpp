#include "megahttp_resource.h"

#include <iostream>

#include "mega_client.h"
#include "get_public_node_listener.h"

using namespace std;
using namespace httpserver;
using namespace mega;

#define END_OF_STREAM -1;

class streaming_listener : public MegaTransferListener
{
public:
    virtual void onTransferUpdate(MegaApi *api, MegaTransfer *transfer)
    {
        // auto size = transfer->getDeltaSize();
        // char *data = transfer->getLastBytes();

        // cout << "onTransferData: buf " << (long long)data
        //      << " size " << size << endl;
    }

    virtual void onTransferFinish(MegaApi *api, MegaTransfer *transfer,
                                  MegaError *err)
    {
        // cout << "onTransferFinish: " << err << endl;
    }
};

ssize_t response_callback(char *buf, size_t size)
{
    return -1;
}

void megahttp_resource::render_GET(const http_request &req, http_response **res)
{
    string mega_url = req.get_arg("url");
    // TODO check mega_url

    cout << "url: " << mega_url << endl;

    // TODO use exceptions to handle errors
    // TODO don't download every time - make a cache (class)

    // get node
    MegaNode *node = get_mega_public_node(mega_url);
    auto size = node->getSize();

    cout << "node size: " << size << endl;

    // start node download
    // TODO look at HTTP request range !
    streaming_listener listener;
    mega_api->startStreaming(node, 0, size, &listener);

    // associate http callback with http response
    *res = new http_response(http_response_builder("")
                             .deferred_response(response_callback));
}
