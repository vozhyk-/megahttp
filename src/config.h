#ifndef CONFIG_H
#define CONFIG_H

#include <chrono>
#include <string>

#include "logging.h"

extern const int server_port;
extern const int server_max_threads;

extern const size_t max_cache_size;

extern const std::string log_file;
extern logging::logger::logged_types_map logged_types;
extern int mega_log_level;

#endif // CONFIG_H
