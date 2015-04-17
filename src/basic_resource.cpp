#include "basic_resource.h"

#include "http_server.h"
#include "mega_client.h"
#include "logging.h"

using namespace std;
using namespace httpserver;
using namespace mega;
using namespace logging;


http_response *basic_resource::make_msg_response(const string &msg,
                                                 int status_code)
{
    logger.log(msg_type::response_msg)
        << msg << endl;

    return new http_response(http_response_builder(msg + '\n', status_code)
                             .string_response());
}

string basic_resource::path_to_string(basic_resource::str_iter beg,
                                      basic_resource::str_iter end)
{
    return accumulate(beg, end, string{},
                      [](const string &a, const string &b) {
                          return a + '/' + b;
                      });
}
