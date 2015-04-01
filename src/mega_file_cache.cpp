#include "mega_file_cache.h"

mega_file_cache::mega_file_cache(string temp_dir)
{
    this->temp_dir = temp_dir;
}

string mega_file_cache::get_public_file(string url)
{
    MegaNode *node = get_mega_public_node(url);

    string local_path = node_local_path(node);

    return download_cache.get(node);
}
