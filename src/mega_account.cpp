#include "mega_account.h"

#include "mega_client.h"

using namespace std;
using namespace mega;


mega_account::mega_account(const string &username,
                           const string &password)
    : MegaApi(app_key)
{
    login_listener listener;
    login(username.c_str(), password.c_str(), &listener);

    shared_ptr<MegaError> error = listener.wait_for_result();

    switch (error->getErrorCode())
    {
    case MegaError::API_ENOENT: // email/password invalid
    case MegaError::API_EARGS:  // Invalid argument
        // We don't make a distinction, maybe we should?
        throw invalid_credentials{};

    case MegaError::API_OK:
        return;

    default:
        throw other_login_error{error};
    }
}

void mega_account::login_listener::onRequestFinish(MegaApi *,
                                                   MegaRequest *,
                                                   MegaError *error)
{
    result = shared_ptr<MegaError>(new MegaError(*error));
    done = true;
}
