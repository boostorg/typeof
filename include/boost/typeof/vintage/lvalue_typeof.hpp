// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_VINTAGE_LVALUE_TYPEOF_HPP_INCLUDED
#define BOOST_VINTAGE_LVALUE_TYPEOF_HPP_INCLUDED

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

        char(*classify_expression(...))[
            RVALUE
        ];

        template<class T>
        char(*classify_expression(T&))[
            is_const<T>::value ? CONST_LVALUE : LVALUE
        ];
        template<int n> 
        struct decorate_type_impl {
            template<typename T>
            struct inner {
                typedef T type;
            };
        };
        template<> 
        struct decorate_type_impl<LVALUE> {
            template<typename T>
            struct inner {
                typedef T& type;
            };
        };

        template<>
        struct decorate_type_impl<CONST_LVALUE> {
            template<typename T>
            struct inner {
                typedef T const& type;
            };
        };

        template<class T, int n> struct decorate_type
        {
            typedef decorate_type_impl<n>::inner<T>::type type;
        };
    }
}

// Since this is always a type, 
// just add "typename" when using in templates

#define BOOST_LVALUE_TYPEOF(expr)                           \
    boost::type_of::decorate_type<                          \
        BOOST_TYPEOF(expr),                                 \
        sizeof(*boost::type_of::classify_expression(expr))  \
    >::type


#endif //BOOST_VINTAGE_LVALUE_TYPEOF_HPP_INCLUDED