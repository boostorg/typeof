// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_CONCATENATE_HPP_INCLUDED
#define BOOST_TYPEOF_CONCATENATE_HPP_INCLUDED

#include <boost/mpl/vector.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

// Assumes iter0 contains initial iterator

#define BOOST_TYPEOF_DECODE_PARAM(z, n, text)   \
    typedef decode_type<iter##n> decode##n;     \
    typedef typename decode##n::type p##n;      \
    typedef typename decode##n::iter BOOST_PP_CAT(iter, BOOST_PP_INC(n));

#define BOOST_TYPEOF_DECODE_PARAMS(n)\
    BOOST_PP_REPEAT(n, BOOST_TYPEOF_DECODE_PARAM, ~)

// The P0, P1, ... PN are encoded and added to V 

#define BOOST_TYPEOF_ENCODE_PARAMS_BEGIN(z, n, text)\
    typename encode_type<

#define BOOST_TYPEOF_ENCODE_PARAMS_END(z, n, text)\
    , BOOST_PP_CAT(P, n)>::type

#define BOOST_TYPEOF_ENCODE_PARAMS(n, ID)                                   \
    BOOST_PP_REPEAT(n, BOOST_TYPEOF_ENCODE_PARAMS_BEGIN, ~)                 \
    typename BOOST_TYPEOF_PUSH_BACK<V, mpl::size_t<ID> >::type              \
    BOOST_PP_REPEAT(n, BOOST_TYPEOF_ENCODE_PARAMS_END, ~)

// constant-time push_back for mpl::vector
// to be removed once real one is available from MPL

#define BOOST_TYPEOF_spec_push_back(z, i, text)                     \
    template<class T BOOST_PP_ENUM_TRAILING_PARAMS(i, class T)>     \
    struct push_back<BOOST_PP_CAT(mpl::vector, i)<BOOST_PP_ENUM_PARAMS(i, T)>, T> \
    {                                                               \
        typedef BOOST_PP_CAT(mpl::vector, BOOST_PP_INC(i))<         \
        BOOST_PP_ENUM_PARAMS(i, T) BOOST_PP_COMMA_IF(i) T           \
        > type;                                                     \
    };                                                              \

#define BOOST_TYPEOF_implement_push_back()          \
    template<class V, class T> struct push_back;    \
    BOOST_PP_REPEAT(                                \
        BOOST_TYPEOF_LIMIT_SIZE,                    \
        BOOST_TYPEOF_spec_push_back,                \
        ~                                           \
    )                                               \

namespace boost{namespace type_of{namespace detail{
    BOOST_TYPEOF_implement_push_back()
}}}

#undef BOOST_TYPEOF_spec_push_back
#undef BOOST_TYPEOF_implement_push_back

#endif//BOOST_TYPEOF_CONCATENATE_HPP_INCLUDED
