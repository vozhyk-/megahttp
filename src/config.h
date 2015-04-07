#ifndef CONFIG_H
#define CONFIG_H

#include <chrono>

const auto mega_request_sleep = std::chrono::milliseconds(200);
const auto http_response_sleep = std::chrono::milliseconds(200);

#endif /* CONFIG_H */
