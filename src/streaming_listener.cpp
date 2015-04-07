#include "streaming_listener.h"
#include "file_cache_item.h"

streaming_listener::streaming_listener(file_cache_item &cache_item)
    : cache_item(cache_item)
{
}

void streaming_listener::onTransferUpdate(MegaApi *api,
                                          MegaTransfer *transfer)
{
    auto size = transfer->getDeltaSize();
    char *data = transfer->getLastBytes();

    cache_item.append_data(data, size);
}

void streaming_listener::onTransferFinish(MegaApi *api,
                                          MegaTransfer *transfer,
                                          MegaError *err)
{
    // TODO look at err
    cache_item.downloading = false;
}
