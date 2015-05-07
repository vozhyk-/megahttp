#include "logging_utils.h"

#include "logging.h"
#include "mega_client.h"
#include "http_utils.h"

using namespace std;
using namespace httpserver;
using namespace mega;
using namespace logging;


namespace logging
{
    /*!
     * @return string for identifying a node in log output
     *
     * Not const because .getBase64Handle() is not
     */
    string node_id(MegaNode &node)
    {
        return "(" + string{node.getBase64Handle()} + ") ";
    }

    void log_headers(const http_request &req)
    {
        const auto t = msg_type::request_headers;
        if (logger.will_log(t))
        {
            map<string, string, header_comparator> headers;
            req.get_headers(headers);
            for (auto i : headers)
                logger.log(t)
                    << "  " << i.first << ": " << i.second << endl;
        }
    }

    void log_path(const vector<string> &path)
    {
        logger.log(msg_type::login_request_path)
            << path_to_string(path.begin(), path.end()) << endl;
    }

    // not const because .get* functions aren't
    void log_node(MegaNode &node)
    {
        string id = node_id(node);
        logger.log(msg_type::file_info)
            << id << "file name: " << node.getName() << endl;
        logger.log(msg_type::file_info)
            << id << "file size: " << node.getSize() << endl;
    }
}
