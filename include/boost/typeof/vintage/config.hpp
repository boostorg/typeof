// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#include <boost/preprocessor/cat.hpp>
#include <boost/detail/workaround.hpp>

#ifndef BOOST_TYPEOF_VINTAGE_CONFIG_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_CONFIG_HPP_INCLUDED

#ifndef BOOST_MAX_TYPEOF_COUNTER
#define BOOST_MAX_TYPEOF_COUNTER 1000
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
# define BOOST_MIN_TYPEOF_COUNTER 5
#else 
# define BOOST_MIN_TYPEOF_COUNTER 1
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#define TYPEOF_MSVC_ETI_WRAPPER(name)                                           \
namespace boost { namespace type_of { namespace detail                          \
{                                                                               \
    template <typename T>                                                       \
    struct BOOST_PP_CAT(get_, name)                                             \
    {                                                                           \
        typedef typename T::name type;                                          \
    };                                                                          \
                                                                                \
    template <>                                                                 \
    struct BOOST_PP_CAT(get_, name)<int>                                        \
    {                                                                           \
        typedef int type;                                                       \
    };                                                                          \
}}}
#endif //BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
TYPEOF_MSVC_ETI_WRAPPER(next)
# define TYPEOF_GET_NEXT(T) ::boost::type_of::detail::get_next<T>::type
#else
# define TYPEOF_GET_NEXT(T) typename T::next
#endif

#if BOOST_WORKAROUND(__BORLANDC__, <= 0x551)                                    \
    || BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
namespace boost { namespace type_of { namespace detail
{
    template <typename T>
    struct get_value
    {
        BOOST_STATIC_CONSTANT(int, value = T::value);
    };

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

    // VC6 ETI (early template instantiation) bug workaround.
    template <>
    struct get_value<int>
    {
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
#endif
}}}
#endif

#if BOOST_WORKAROUND(__BORLANDC__, <= 0x551)                                    \
    || BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
# define TYPEOF_GET_VALUE(T) ::boost::type_of::detail::get_value<T>::value
#else
# define TYPEOF_GET_VALUE(T) T::value
#endif

#endif //BOOST_TYPEOF_VINTAGE_CONFIG_HPP_INCLUDED
