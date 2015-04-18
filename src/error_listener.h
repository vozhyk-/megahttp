#ifndef ERROR_LISTENER_H
#define ERROR_LISTENER_H

#include <megaapi.h>

#include "result_listener.h"


class error_listener
    : public result_listener<std::shared_ptr<mega::MegaError>>,
      public mega::MegaRequestListener
{
    void onRequestFinish(mega::MegaApi *,
                         mega::MegaRequest *,
                         mega::MegaError *error)
    {
        using std::shared_ptr;
        using mega::MegaError;

        result = shared_ptr<MegaError>(new MegaError(*error));
        done = true;
    }
};

#endif // ERROR_LISTENER_H
