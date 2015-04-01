#ifndef MEGA_CLIENT_H
#define MEGA_CLIENT_H

#include <megaapi.h>

extern mega::MegaApi *mega_api;

void init_mega();

mega::MegaNode *get_mega_public_node(std::string url)
std::string download_public_file_to_tmp(std::string url);

#endif // MEGA_CLIENT_H
