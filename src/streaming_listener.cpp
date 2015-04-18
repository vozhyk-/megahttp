#include "streaming_listener.h"

#include <iostream>

#include "logging.h"
#include "logging_utils.h"
#include "mega_client.h"
#include "file_cache_item.h"

using namespace std;
using namespace mega;

using namespace logging;

streaming_listener::streaming_listener(file_cache_item &cache_item)
    : cache_item{cache_item}
{
}

void streaming_listener::onTransferStart(MegaApi *api,
                                         MegaTransfer *transfer)
{
    id = node_id(*cache_item.node);

    logger.log(msg_type::download_status)
        << id
        << "starting" << endl;
}

void streaming_listener::onTransferUpdate(MegaApi *api,
                                          MegaTransfer *transfer)
{
    auto size = transfer->getDeltaSize();
    char *data = transfer->getLastBytes();

    cache_item.append_data(data, size);

    logger.log(msg_type::download_data)
        << id
        << "size " << size
        << ", new buffer size: " << cache_item.buffer.size()
        << endl;
}

void streaming_listener::onTransferFinish(MegaApi *api,
                                          MegaTransfer *transfer,
                                          MegaError *err)
{
    // TODO look at err
    cache_item.downloading = false;

    logger.log(msg_type::download_status)
        << id
        << "finished with " << err->getErrorString() << "." << endl;
}
