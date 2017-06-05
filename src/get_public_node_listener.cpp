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
        set_result(unique_ptr<MegaNode>{
                request->getPublicMegaNode()});
    else
        set_result(nullptr);
}
