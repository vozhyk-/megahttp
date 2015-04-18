#ifndef MEGA_CLIENT_H
#define MEGA_CLIENT_H

#include <memory>
#include <unordered_map>
#include <megaapi.h>

#include "mega_account.h"


extern const char *app_key;

extern std::unique_ptr<mega::MegaApi> mega_api;
extern std::unordered_map<std::string, std::unique_ptr<mega_account>>
    mega_accounts;


void init_mega();

void add_account(const std::string &username,
                 const std::string &password);

std::shared_ptr<mega::MegaError> get_mega_public_node(
    std::string url,
    std::unique_ptr<mega::MegaNode> &result);

#endif // MEGA_CLIENT_H
