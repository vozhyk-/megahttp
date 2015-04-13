#include "mega_logger.h"

#include "logging.h"

using namespace std;
using namespace mega;
using namespace logging;


void mega_logger::log(const char *time,
                      int loglevel,
                      const char *source,
                      const char *message)
{
    auto &log = logger->log(msg_type::mega_msg);

    log << str_log_level(loglevel);

    if (logger->will_log(msg_type::mega_msg_source_location))
        log << "[" << source << "] ";

    log << message << endl;
}

string mega_logger::str_log_level(int level)
{
    switch (level)
    {
    case MegaApi::LOG_LEVEL_FATAL:   return "[fatal] ";
    case MegaApi::LOG_LEVEL_ERROR:   return "[error] ";
    case MegaApi::LOG_LEVEL_WARNING: return "[warn] ";
    case MegaApi::LOG_LEVEL_INFO:    return "";
    case MegaApi::LOG_LEVEL_DEBUG:   return "[debug] ";
    case MegaApi::LOG_LEVEL_MAX:     return "[max] ";
    // shouldn't happen
    default:                         return "";
    }
}
