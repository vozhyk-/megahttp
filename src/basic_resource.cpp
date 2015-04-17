#include "basic_resource.h"

#include "http_server.h"
#include "logging.h"

using namespace std;
using namespace httpserver;
using namespace logging;


http_response *basic_resource::make_msg_response(const string &msg,
                                                 int status_code)
{
    logger.log(msg_type::response_msg)
        << msg << endl;

    return new http_response(http_response_builder(msg + '\n', status_code)
                             .string_response());
}

void basic_resource::log_headers(const http_request &req)
{
    const auto t = msg_type::request_info;
    if (logger.will_log(t))
    {
        logger.log(t) << "Headers:" << endl;

        map<string, string, header_comparator> headers;
        req.get_headers(headers);
        for (auto i : headers)
            logger.log(t)
                << "  " << i.first << ": " << i.second << endl;
    }
}

void basic_resource::log_path(const vector<string> &path)
{
    logger.log(msg_type::login_request_path)
        << path_to_string(path.begin(), path.end()) << endl;
}

string basic_resource::path_to_string(basic_resource::str_iter beg,
                                      basic_resource::str_iter end)
{
    return accumulate(beg, end, string{},
                      [](const string &a, const string &b) {
                          return a + '/' + b;
                      });
}
