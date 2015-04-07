#include "streaming_listener.h"

#include <iostream>

#include "file_cache_item.h"

using namespace std;

streaming_listener::streaming_listener(file_cache_item &cache_item)
    : cache_item(cache_item)
{
}

void streaming_listener::onTransferStart(MegaApi *api,
                                         MegaTransfer *transfer)
{
    cout << "Download starting" << endl;
}

void streaming_listener::onTransferUpdate(MegaApi *api,
                                          MegaTransfer *transfer)
{
    auto size = transfer->getDeltaSize();
    char *data = transfer->getLastBytes();

    cache_item.append_data(data, size);

    cout << "Downloaded data: size " << size
         << ", new buffer size: " << cache_item.buffer.size()
         << endl;
}

void streaming_listener::onTransferFinish(MegaApi *api,
                                          MegaTransfer *transfer,
                                          MegaError *err)
{
    // TODO look at err
    cache_item.downloading = false;

    cout << "Download finished with " << err->getErrorString() << endl;
}
