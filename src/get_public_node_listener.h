#ifndef GET_PUBLIC_NODE_LISTENER_H
#define GET_PUBLIC_NODE_LISTENER_H

#include "mega_client.h"
#include "listener_base.h"


class get_public_node_listener
    : public listener_base<mega::MegaNode *>, public mega::MegaRequestListener
{
public:
    void onRequestFinish(mega::MegaApi *,
                         mega::MegaRequest *,
                         mega::MegaError *);
};

#endif // GET_PUBLIC_NODE_LISTENER_H
