#ifndef MEGA_LOGGER_H
#define MEGA_LOGGER_H

#include <megaapi.h>

#include "logging.h"

class mega_logger : public mega::MegaLogger
{
    class logging::logger *logger;

    std::string str_log_level(int level);
public:
    mega_logger(class logging::logger *logger) : logger{logger} {}

    void log(const char *time,
             int loglevel,
             const char *source,
             const char *message);
};

#endif // MEGA_LOGGER_H
