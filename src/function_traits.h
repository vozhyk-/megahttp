#ifndef FUNCTION_TRAITS_H
#define FUNCTION_TRAITS_H

/*
 * function_traits
 * Taken from http://stackoverflow.com/a/7943765
 * and modified
 * Usage example there
 */

template <typename T>
struct function_traits
    : public function_traits<decltype(&T::operator())>
{};
// For generic types, directly use the result of the signature of its 'operator()'

template <typename class_type, typename return_type, typename... args>
struct function_traits<return_type(class_type::*)(args...) const>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(args) };
    // arity is the number of arguments.

    using result_type = return_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};


template<typename function>
using result_type = typename function_traits<function>::result_type;

#endif // FUNCTION_TRAITS_H
