// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_TYPEOF_IMPL_HPP_INCLUDED
#define BOOST_TYPEOF_TYPEOF_IMPL_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/typeof/encode_decode.hpp>

#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/push_back.hpp>

#ifdef BOOST_TYPEOF_USE_MPL_VECTOR
#   include <boost/mpl/vector.hpp>
#   include <boost/typeof/limit_size.hpp>
#   define BOOST_TYPEOF_VECTOR(n) BOOST_PP_CAT(boost::mpl::vector, n)
#else
#   include <boost/typeof/vector.hpp>
#   define BOOST_TYPEOF_VECTOR(n) BOOST_PP_CAT(boost::type_of::vector, n)
#endif

namespace boost{namespace type_of{

    template<int pos, class T>
    struct at_result
    {
        typedef typename encode_type<BOOST_TYPEOF_VECTOR(0)<>, T>::type encoded_type;
        typedef typename mpl::size<encoded_type>::type size;

        typedef char(&type)[
            mpl::at<
                encoded_type,
                mpl::int_<(pos < size::value) ? pos : 0>
            >::type::value
        ];
    };
    
    template<int pos, class T>
        typename at_result<pos, T>::type at(const T&);

    template<class T>
        char(&size(const T&))[
            mpl::size<typename encode_type<BOOST_TYPEOF_VECTOR(0)<>, T>::type>::value
        ];
}}

#define BOOST_TYPEOF_AT(n, expr) sizeof(boost::type_of::at<n>(expr))
#define BOOST_TYPEOF_SIZE(expr) sizeof(boost::type_of::size(expr))

#ifndef BOOST_TYPEOF_NO_SIMPLE_TYPE_OPTIMIZATION
#   define BOOST_TYPEOF_TYPEITEM(z, n, expr)\
    boost::mpl::size_t<BOOST_TYPEOF_AT((n < BOOST_TYPEOF_SIZE(expr)) ? n : 0, expr)>
#else
#   define BOOST_TYPEOF_TYPEITEM(z, n, expr)\
    boost::mpl::size_t<BOOST_TYPEOF_AT(n, expr)>
#endif

#define BOOST_TYPEOF(Expr)                                                          \
    boost::type_of::decode_type<                                                    \
        boost::mpl::begin<                                                          \
            BOOST_TYPEOF_VECTOR(BOOST_TYPEOF_LIMIT_SIZE)<                           \
                BOOST_PP_ENUM(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_TYPEITEM, Expr) \
            >                                                                       \
        >::type                                                                     \
    >::type

#define BOOST_TYPEOF_TPL(Expr)                                                      \
    typename boost::type_of::decode_type<                                           \
        typename boost::mpl::begin<                                                 \
            BOOST_TYPEOF_VECTOR(BOOST_TYPEOF_LIMIT_SIZE)<                           \
                BOOST_PP_ENUM(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_TYPEITEM, Expr) \
            >                                                                       \
        >::type                                                                     \
    >::type

#endif//BOOST_TYPEOF_COMPLIANT_TYPEOF_IMPL_HPP_INCLUDED
