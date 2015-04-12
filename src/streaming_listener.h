#ifndef STREAMING_LISTENER_H
#define STREAMING_LISTENER_H

#include <megaapi.h>

using namespace mega;

class file_cache_item;

class streaming_listener : public MegaTransferListener
{
    file_cache_item &cache_item;

    std::string id;

public:
    streaming_listener(file_cache_item &cache_item);

    virtual void onTransferStart(MegaApi *, MegaTransfer *);
    virtual void onTransferUpdate(MegaApi *, MegaTransfer *);
    virtual void onTransferFinish(MegaApi *, MegaTransfer *, MegaError *);
};

#endif // STREAMING_LISTENER_H
