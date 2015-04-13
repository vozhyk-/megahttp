#include "basic_resource.h"

#include "http_server.h"
#include "logging.h"

using namespace std;
using namespace httpserver;
using namespace logging;


http_response *basic_resource::make_error_response(const string &msg,
                                                   int status_code)
{
    logger.log(msg_type::response_error)
        << msg << endl;

    return new http_response(http_response_builder(msg + '\n', status_code)
                             .string_response());
}
