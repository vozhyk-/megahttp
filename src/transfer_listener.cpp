#include "transfer_listener.h"

using namespace mega;

void transfer_listener::onTransferFinish(MegaApi *api,
                                         MegaTransfer *transfer,
                                         MegaError *error)
{
    result = error->getErrorCode() == MegaError::API_OK;
    done = true;
}
