#include "logging.h"
#include "mega_client.h"
#include "http_server.h"

using namespace std;

int main()
{
    logging::init_logging();
    init_mega();
    start_http_server();

    return 0;
}
