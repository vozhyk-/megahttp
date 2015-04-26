#include "get_public_node_listener.h"

using namespace std;
using namespace mega;


void get_public_node_listener::onRequestFinish(MegaApi *,
                                               MegaRequest *request,
                                               MegaError *err)
{
    /* make a copy —
     * original err is deleted in MEGA SDK code
     */
    error = shared_ptr<MegaError>(
        new MegaError(*err));

    if (error->getErrorCode() == MegaError::API_OK)
        promise.set_value(unique_ptr<MegaNode>{
                request->getPublicMegaNode()});
    else
        promise.set_value(nullptr);
}
