#include "get_public_node_listener.h"

using namespace std;
using namespace mega;


void get_public_node_listener::onRequestFinish(MegaApi *api,
                                                       MegaRequest *request,
                                                       MegaError *error)
{
    if (error->getErrorCode() == MegaError::API_OK)
        result = request->getPublicMegaNode();

    done = true;
}
