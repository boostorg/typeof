// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_TYPEOF_IMPL_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_TYPEOF_IMPL_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

#define BOOST_TYPEOF_PUSH_BACK detail::push_back
//#define BOOST_TYPEOF_PUSH_BACK mpl::push_back

#include <boost/typeof/compliant/limit_size.hpp>
#include <boost/typeof/compliant/encode_decode.hpp>

namespace boost
{
    namespace type_of
    {
        template<int pos, class T>
            char(&at(const T&))[
                mpl::at<typename encode_type<mpl::vector0<>, T>::type, mpl::size_t<pos> >::type::value
            ];

        template<class T>
            char(&size(const T&))[
                mpl::size<typename encode_type<mpl::vector0<>, T>::type>::value
            ];
    }
}

#define BOOST_TYPEOF_AT(n, expr) sizeof(boost::type_of::at<n>(expr))
#define BOOST_TYPEOF_SIZE(expr) sizeof(boost::type_of::size(expr))

#define BOOST_TYPEOF_TYPEITEM(z, n, expr)\
    boost::mpl::size_t<BOOST_TYPEOF_AT((n < BOOST_TYPEOF_SIZE(expr)) ? n : 0, expr)>

#define BOOST_TYPEOF(Expr)                                                          \
    boost::type_of::decode_type<                                                    \
        boost::mpl::begin<                                                          \
            BOOST_PP_CAT(boost::mpl::vector, BOOST_TYPEOF_LIMIT_SIZE)<              \
                BOOST_PP_ENUM(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_TYPEITEM, Expr) \
            >                                                                       \
        >::type                                                                     \
    >::type

#define BOOST_TYPEOF_TPL(Expr)                                                      \
    typename boost::type_of::decode_type<                                           \
        typename boost::mpl::begin<                                                 \
            BOOST_PP_CAT(boost::mpl::vector, BOOST_TYPEOF_LIMIT_SIZE)<              \
                BOOST_PP_ENUM(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_TYPEITEM, Expr) \
            >                                                                       \
        >::type                                                                     \
    >::type

#endif//BOOST_TYPEOF_COMPLIANT_TYPEOF_IMPL_HPP_INCLUDED
