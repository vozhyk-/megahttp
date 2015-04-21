#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <map>

#include "null_ostream.h"


namespace logging
{
    /* To add a new msg_type:
     *   add it to this enum
     *   add its description to logging.cpp:type_description
     *   add an option for it in config.cpp:logged_types
     */
    enum class msg_type
    {
        mega_msg,
        mega_msg_source_location,
        request_info,
        login_request_path,
        response_msg,
        file_info,
        response_status,
        response_data,
        download_status,
        download_data,
        file_cache_gc,
    };

    std::ostream &operator<<(std::ostream &out, msg_type type);

    class logger : public std::ofstream
    {
    public:
        using logged_types_map = std::map<msg_type, bool>;

        logger(logged_types_map &logged_types) : logged(logged_types) {}

        std::ostream &log(msg_type type);
        bool will_log(msg_type type);
    private:
        null_ostream null_stream;

        logged_types_map &logged;
    };


    void init_logging();


    extern class logger logger;
}

#endif // LOGGER_H
