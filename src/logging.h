#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <map>

#include "null_ostream.h"


namespace logging
{
    enum class msg_type
    {
        request_info,
        response_error,
        file_info,
        response_data,
        download_status,
        download_data,
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
