#ifndef ACCOUNT_FILES_H
#define ACCOUNT_FILES_H

#include <httpserver.hpp>


class account_files_resource
    : public httpserver::http_resource<account_files_resource>
{
    httpserver::http_response *make_GET_response(
        const httpserver::http_request &);
public:
    void render_GET(const httpserver::http_request &,
                    httpserver::http_response **);
};

#endif // ACCOUNT_FILES_H
