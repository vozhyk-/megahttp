#include "config.h"

using namespace logging;
using namespace std;

const int server_port = 8080;
const int server_max_threads = 2;

const string log_file = "megahttp.log";
// Types of messages that should be logged
logger::logged_types_map logged_types
{
    // variables from HTTP request
    { msg_type::request_info, true },
    // error HTTP server returns to client
    { msg_type::response_error, true },
    // info about requested files
    { msg_type::file_info, true },
    // download start/finish, error
    { msg_type::download_status, true },

    // chunks returned to HTTP client (a lot of output)
    { msg_type::response_data, false },
    // chunks downloaded from MEGA    (a lot of output)
    { msg_type::download_data, false },
};

/* Time to wait before checking the state again */
const auto mega_request_sleep = chrono::milliseconds(200);
const auto http_response_sleep = chrono::milliseconds(200);
