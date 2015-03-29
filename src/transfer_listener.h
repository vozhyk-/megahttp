#ifndef TRANSFER_LISTENER_H
#define TRANSFER_LISTENER_H

#include <megaapi.h>
#include "listener_base.h"

using namespace mega;

class transfer_listener
    : public listener_base<bool>, public MegaTransferListener
{
public:
    virtual void onTransferFinish(MegaApi *, MegaTransfer *, MegaError *);
};

#endif // TRANSFER_LISTENER_H
