#include "logging.h"

#include <ctime>

#include "config.h"

using namespace std;

namespace logging
{
    // not adding const because no operator[] for it
    map<msg_type, string> type_description
    {
        { msg_type::request_info, "request" },
        { msg_type::file_info, "file info" },
        { msg_type::response_data, "response data" },
        { msg_type::download_status, "download" },
        { msg_type::download_data, "download data" },
    };

    string date()
    {
        time_t sec = time(nullptr);
        tm *t = localtime(&sec); // possible data race
        char time_s[20];

        strftime(time_s, 20, "%F %T", t);
        return string(time_s);
    }

    ostream &logger::log(msg_type type)
    {
        if (will_log(type))
        {
            (*this) << date() << " [" << type << "] ";
            return (*this);
        }
        else
        {
            return null_stream;
        }
    }

    bool logger::will_log(msg_type type)
    {
        return logged[type];
    }

    ostream &operator<<(ostream &out, msg_type type)
    {
        return out << type_description[type];
    }

    class logger logger(logged_types);

    void init_logging()
    {
        logger.open(log_file);
    }
}