#include "streaming_listener.h"

#include <iostream>

#include "logging.h"
#include "file_cache_item.h"

using namespace std;
using namespace logging;

streaming_listener::streaming_listener(file_cache_item &cache_item)
    : cache_item(cache_item)
{
}

void streaming_listener::onTransferStart(MegaApi *api,
                                         MegaTransfer *transfer)
{
    logger.log(msg_type::download_status)
        << "starting" << endl;
}

void streaming_listener::onTransferUpdate(MegaApi *api,
                                          MegaTransfer *transfer)
{
    auto size = transfer->getDeltaSize();
    char *data = transfer->getLastBytes();

    cache_item.append_data(data, size);

    logger.log(msg_type::download_data)
        << "size " << size
        << ", new buffer size: " << cache_item.buffer.size()
        << ", node " << cache_item.node->getBase64Handle()
        << endl;
}

void streaming_listener::onTransferFinish(MegaApi *api,
                                          MegaTransfer *transfer,
                                          MegaError *err)
{
    // TODO look at err
    cache_item.downloading = false;

    logger.log(msg_type::download_status)
        << "finished with " << err->getErrorString() << "." << endl;
}
