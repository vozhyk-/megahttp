#include "mega_client.h"

#include <megaapi.h>

using namespace std;
using namespace mega;


const char *APP_KEY = "HUc2iQaJ";

void init_mega()
{
    // TODO investigate enabling local caching
    MegaApi *megaApi = new MegaApi(APP_KEY);

    megaApi->setLogLevel(MegaApi::LOG_LEVEL_INFO);
}
