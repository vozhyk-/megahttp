#include "config.h"

#include <megaapi.h>

using namespace std;
using namespace mega;
using namespace logging;


const int server_port = 8080;
const int server_max_threads = 5;

/*
 * Maximum size of cache's buffers in bytes.
 * Cache can grow bigger than this amount if e.g.
 *   a file is bigger than the size limit
 * or
 *   when all files in the cache are being used
 *   at the time of garbage collection.
 */
const size_t max_cache_size = 100*1024*1024;

const string log_file = "megahttp.log";
// Types of messages that should be logged
logger::logged_types_map logged_types
{
    // log messages from MEGA SDK according to mega_log_level
    { msg_type::mega_msg, true },
    // variables from HTTP request
    { msg_type::request_info, true },
    // path of login HTTP request
    { msg_type::login_request_path, true },
    // messages server returns to client
    { msg_type::response_msg, true },
    // info about requested files
    { msg_type::file_info, true },
    // streaming finish
    { msg_type::response_status, true },
    // download start/finish, error
    { msg_type::download_status, true },
    // file cache's garbage collector working details
    { msg_type::file_cache_gc, true },

    // headers of HTTP requests
    // warning: if enabled, authorization data is logged too
    { msg_type::request_headers, false },
    // chunks returned to HTTP client (a lot of output)
    { msg_type::response_data, false },
    // chunks downloaded from MEGA    (a lot of output)
    { msg_type::download_data, false },
    // source location in mega_msg
    { msg_type::mega_msg_source_location, false },
};
int mega_log_level = MegaApi::LOG_LEVEL_INFO;

/* Time to wait before checking the state again */
const auto http_response_sleep = chrono::milliseconds(200);
