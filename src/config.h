#ifndef CONFIG_H
#define CONFIG_H

#include <chrono>
#include <string>

#include "logging.h"

extern const int server_port;
extern const int server_max_threads;

extern const std::string log_file;
extern logging::logger::logged_types_map logged_types;

extern const std::chrono::milliseconds mega_request_sleep;
extern const std::chrono::milliseconds http_response_sleep;

#endif // CONFIG_H
