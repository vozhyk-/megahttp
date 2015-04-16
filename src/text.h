#ifndef TEXT_H
#define TEXT_H

#include <string>

namespace response_msg
{
    using str = const std::string;

    extern str empty_url;
    extern str node_not_found;
    extern str failed_to_get_node;

    extern str invalid_file_req_path;
    extern str not_logged_in;

    extern str path_email_not_specified;
    extern str log_in;
    extern str mega_login_successful;
    extern str already_logged_in;
    extern str invalid_credentials;
    extern str mega_login_failed;
}

#endif // TEXT_H
