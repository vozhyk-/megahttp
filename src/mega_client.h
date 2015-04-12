#ifndef MEGA_CLIENT_H
#define MEGA_CLIENT_H

#include <memory>
#include <megaapi.h>

extern std::unique_ptr<mega::MegaApi> mega_api;

void init_mega();

std::string node_id(std::shared_ptr<mega::MegaNode> node);

std::shared_ptr<mega::MegaError> get_mega_public_node(
    std::string url,
    std::shared_ptr<mega::MegaNode> &result);
std::string download_public_file_to_tmp(std::string url);

#endif // MEGA_CLIENT_H
