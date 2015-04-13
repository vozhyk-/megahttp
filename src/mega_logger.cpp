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
    // TODO don't ignore loglevel - print it
    auto &log = logger->log(msg_type::mega_msg);

    if (logger->will_log(msg_type::mega_msg_source_location))
        log << "[" << source << "] ";

    log << message << endl;
}
