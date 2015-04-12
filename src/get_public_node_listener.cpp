#include "get_public_node_listener.h"

using namespace std;
using namespace mega;


void get_public_node_listener::onRequestFinish(MegaApi *api,
                                               MegaRequest *request,
                                               MegaError *err)
{
    error = shared_ptr<MegaError>(
        new MegaError(*err));
    // original err is deleted in MEGA SDK code

    if (error->getErrorCode() == MegaError::API_OK)
        result = shared_ptr<MegaNode>(
            request->getPublicMegaNode());

    done = true;
}
