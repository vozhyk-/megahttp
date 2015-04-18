#ifndef MEGA_ACCOUNT_H
#define MEGA_ACCOUNT_H

#include <memory>
#include <megaapi.h>

#include "error_listener.h"


class mega_account : public mega::MegaApi
{
    class error_listener fetch_nodes_listener;

    void fetch_nodes_start();

public:
    class login_error : public std::exception
    {
    };

    class invalid_credentials
        : public login_error, public std::invalid_argument
    {
    public:
        invalid_credentials() : std::invalid_argument("invalid login/password")
        {
        }
    };

    class other_login_error
        : public login_error, public std::runtime_error
    {
    public:
        using mega_error_p = std::shared_ptr<mega::MegaError>;

        other_login_error(mega_error_p err)
            : std::runtime_error("login error"), error{err}
        {
        }

        mega_error_p error;
    };

    mega_account(const std::string &username,
                 const std::string &password);

    std::unique_ptr<mega::MegaNode> get_node_by_path(std::string path);
};

#endif // MEGA_ACCOUNT_H
