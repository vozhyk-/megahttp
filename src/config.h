#ifndef CONFIG_H
#define CONFIG_H

#include <chrono>

const int server_port = 8080;

const auto mega_request_sleep = std::chrono::milliseconds(200);
const auto http_response_sleep = std::chrono::milliseconds(200);

#endif /* CONFIG_H */
