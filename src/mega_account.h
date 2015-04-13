#ifndef MEGA_ACCOUNT_H
#define MEGA_ACCOUNT_H

#include <memory>
#include <megaapi.h>

#include "listener_base.h"


class mega_account : public mega::MegaApi
{
    class login_listener
        : public listener_base<std::shared_ptr<mega::MegaError>>,
          public mega::MegaRequestListener
    {
        void onRequestFinish(mega::MegaApi *,
                             mega::MegaRequest *,
                             mega::MegaError *);
    };

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
};

#endif // MEGA_ACCOUNT_H
