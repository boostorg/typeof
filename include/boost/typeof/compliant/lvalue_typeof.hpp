// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_LVALUE_TYPEOF_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_LVALUE_TYPEOF_HPP_INCLUDED

#include <boost/type_traits/is_const.hpp>

namespace boost
{
    namespace type_of
    {
        enum
        {
            RVALUE = 1,
            LVALUE,
            CONST_LVALUE
        };

        char(&classify_expression(...))[
            RVALUE
        ];

        template<class T>
        char(&classify_expression(T&))[
            is_const<T>::value ? CONST_LVALUE : LVALUE
        ];

        template<class T, int n> struct decorate_type
        {
            typedef T type;
        };
        template<class T> struct decorate_type<T, LVALUE>
        {
            typedef T& type;
        };
        template<class T> struct decorate_type<T, CONST_LVALUE>
        {
            typedef const T& type;
        };
    }
}

// Since this is always a type, 
// just add "typename" when using in templates

#define BOOST_LVALUE_TYPEOF(expr)			                \
    boost::type_of::decorate_type<                          \
        BOOST_TYPEOF(expr),                                 \
        sizeof(boost::type_of::classify_expression(expr))   \
    >::type

#endif//BOOST_TYPEOF_COMPLIANT_LVALUE_TYPEOF_HPP_INCLUDED
