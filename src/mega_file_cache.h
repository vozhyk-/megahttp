#ifndef MEGA_FILE_CACHE_H
#define MEGA_FILE_CACHE_H

class mega_file_cache
{
    class node_download_cache : public cache<MegaNode *, string>
    {
        virtual void store_result(MegaNode *) override;
        virtual string get_cached(MegaNode *) override;
        virtual void store_result(MegaNode *) override;
    } download_cache;
public:
    mega_file_cache(string temp_dir);

    string get_public_file(string url);

    string temp_dir;
};

#endif // MEGA_FILE_CACHE_H
