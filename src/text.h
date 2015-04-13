#ifndef TEXT_H
#define TEXT_H

#include <string>

namespace response_msg
{
    using str = const std::string;

    extern str empty_url;
    extern str node_not_found;
    extern str failed_to_get_node;

    extern str path_email_not_specified;

    extern str mega_login_failed;
}

#endif // TEXT_H
