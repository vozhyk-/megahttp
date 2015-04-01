#include "megahttp_resource.h"

#include <iostream>

#include "mega_client.h"
#include "get_public_node_listener.h"

void megahttp_resource::render_GET(const http_request &req, http_response **res)
{
    string mega_url = req.get_arg("url");
    // TODO check mega_url

    cout << "url: " << mega_url << endl;

    // TODO use exceptions to handle errors
    // TODO don't download every time - make a cache (class)
    string local_path = file_cache->get_public_file(mega_url);

    *res = new http_response(http_response_builder(local_path, 200)
                             .file_response());
}
