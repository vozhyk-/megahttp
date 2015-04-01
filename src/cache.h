#ifndef CACHE_H
#define CACHE_H

template<class arg_type, class result_type>
class cache
{
public:
    virtual bool is_cached(arg_type);
    virtual result_type get_cached(arg_type);
    virtual void store_result(arg_type);

    result_type get(arg_type arg)
    {
        if (is_cached(arg))
        {
            return get_cached(arg);
        }
        else
        {
            store_result(arg);
            return get_cached(arg);
        }
    }
};

// class hashed_cache ...

#endif // CACHE_H
