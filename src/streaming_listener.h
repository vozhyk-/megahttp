#ifndef STREAMING_LISTENER_H
#define STREAMING_LISTENER_H

#include <megaapi.h>


class file_cache_item;

class streaming_listener : public mega::MegaTransferListener
{
    file_cache_item &cache_item;

    std::string id;

public:
    streaming_listener(file_cache_item &cache_item);

    virtual void onTransferStart(mega::MegaApi *, mega::MegaTransfer *);
    virtual void onTransferUpdate(mega::MegaApi *, mega::MegaTransfer *);
    virtual void onTransferFinish(mega::MegaApi *,
                                  mega::MegaTransfer *,
                                  mega::MegaError *);
};

#endif // STREAMING_LISTENER_H
