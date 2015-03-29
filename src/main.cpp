#include "mega_client.h"
#include "http_server.h"

using namespace std;

int main()
{
    init_mega();
    start_http_server();

    return 0;
}
