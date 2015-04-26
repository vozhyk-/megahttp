#ifndef DOWNLOAD_LISTENER_H
#define DOWNLOAD_LISTENER_H

#include <megaapi.h>


class file_cache_item;

class download_listener : public mega::MegaTransferListener
{
    file_cache_item &cache_item;

    std::string id;

public:
    download_listener(file_cache_item &cache_item);

    virtual void onTransferStart(mega::MegaApi *, mega::MegaTransfer *);
    virtual void onTransferUpdate(mega::MegaApi *, mega::MegaTransfer *);
    virtual void onTransferFinish(mega::MegaApi *,
                                  mega::MegaTransfer *,
                                  mega::MegaError *);
};

#endif // DOWNLOAD_LISTENER_H
