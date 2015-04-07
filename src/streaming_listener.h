#ifndef STREAMING_LISTENER_H
#define STREAMING_LISTENER_H

#include <megaapi.h>

using namespace mega;

class file_cache_item;

class streaming_listener : public MegaTransferListener
{
public:
    streaming_listener(file_cache_item &cache_item);

    file_cache_item &cache_item;

    virtual void onTransferUpdate(MegaApi *, MegaTransfer *);
    virtual void onTransferFinish(MegaApi *, MegaTransfer *, MegaError *);
};

#endif // STREAMING_LISTENER_H
