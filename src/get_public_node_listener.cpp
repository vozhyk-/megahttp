#include "get_public_node_listener.h"

using namespace std;
using namespace mega;


void get_public_node_listener::onRequestFinish(MegaApi *api,
                                               MegaRequest *request,
                                               MegaError *err)
{
    /* make a copy —
     * original err is deleted in MEGA SDK code
     */
    error = shared_ptr<MegaError>(
        new MegaError(*err));

    if (error->getErrorCode() == MegaError::API_OK)
        result = unique_ptr<MegaNode>{
            request->getPublicMegaNode()};

    done = true;
}
