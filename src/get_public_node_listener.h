#ifndef GET_PUBLIC_NODE_LISTENER_H
#define GET_PUBLIC_NODE_LISTENER_H

#include "mega_client.h"
#include "listener_base.h"

using namespace mega;

class get_public_node_listener
    : public listener_base<MegaNode *>, public MegaRequestListener
{
public:
    virtual void onRequestFinish(MegaApi *, MegaRequest *, MegaError *);
};

#endif // GET_PUBLIC_NODE_LISTENER_H
