#include "get_public_node_listener.h"

using namespace std;
using namespace mega;

// get_public_node_listener::get_public_node_listener()
// {
//     done = false;
//     result = null;
// }

// MegaNode *get_public_node_listener::wait_for_result()
// {
//     using namespace std::literals;

//     while (!done)
//     {
//         this_thread::sleep_for(1s);
//     }

//     return result;
// }

void get_public_node_listener::onRequestFinish(MegaApi *api,
                                                       MegaRequest *request,
                                                       MegaError *error)
{
    if (error->getErrorCode() == MegaError::API_OK)
        result = request->getPublicMegaNode();

    done = true;
}
