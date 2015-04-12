#include "config.h"

using namespace logging;
using namespace std;

const int server_port = 8080;
const int server_max_threads = 2;

const string log_file = "megahttp.log";
logger::logged_types_map logged_types
{
    { msg_type::request_info, true },
    { msg_type::file_info, true },
    { msg_type::download_status, true },

    { msg_type::response_data, false },
    { msg_type::download_data, false },
};

const auto mega_request_sleep = chrono::milliseconds(200);
const auto http_response_sleep = chrono::milliseconds(200);
