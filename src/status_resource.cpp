#include "status_resource.h"

#include <sstream>

#include "http_server.h"
#include "http_utils.h"
#include "logging_utils.h"
#include "file_cache.h"

using namespace std;
using namespace httpserver;

using namespace logging;


http_response *status_resource::make_GET_response(const http_request &req)
{
    log_headers(req);

    ostringstream res;

    res <<
R"(<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>megahttp status</title>
</head>

<body>
  <h1>megahttp status</h1>
)";

    print_cache_stats(res);

    res <<
R"(
</body>
</html>
)";

    return new http_response(http_response_builder(res.str(),
                                                   status_code::ok,
                                                   "text/html")
                             .string_response());
}

void status_resource::print_cache_stats(ostringstream &res)
{
    res << "<h2>Cache statistics</h2>" << endl;

    res << "<table>" << endl
        << "<th>"
        << " <td>Handle</td>"
        << " <td>In use by</td>"
        << " <td>Filename</td>"
        << " <td>File size</td>"
        << " <td>Memory used</td>"
        << " <td>Downloaded</td>"
        << "</th>" << endl;
    for (auto &i : file_cache.items)
    {
        auto &item = i.second;
        auto &node = item->node;

        res << "<tr>"
            << " <td>" << node->getBase64Handle() << "</td>"
            << " <td>" << item->in_use.get() << "</td>"
            << " <td>" << node->getName() << "</td>"
            << " <td>" << item->full_size << "</td>"
            << " <td>" << item->mem_used() << "</td>"
            << " <td>" << item->have_bytes() << "</td>"
            << "</tr>" << endl;
    }
    res << "</table>" << endl;

    res << "<p>Total memory used (by cache): "
        << file_cache.mem_used()
        << "</p>" << endl;
}

void status_resource::render_GET(const http_request &req,
                                 http_response **res)
{
    *res = make_GET_response(req);
}
