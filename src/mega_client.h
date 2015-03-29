#ifndef MEGA_CLIENT_H
#define MEGA_CLIENT_H

#include <megaapi.h>

extern mega::MegaApi *mega_api;

void init_mega();

void download_public_file(std::string url, std::string local_path);

#endif // MEGA_CLIENT_H
