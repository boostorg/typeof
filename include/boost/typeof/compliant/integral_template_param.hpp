// Copyright (C) 2005 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED

#include <boost/typeof/integral_template_param.hpp>

// INTEGRAL_PARAM "virtual functions" implementation

#define BOOST_TYPEOF_INTEGRAL_PARAM_ENCODE(This, n)\
    typedef typename encode_integral<\
        BOOST_PP_CAT(V, n),\
        BOOST_TYPEOF_INTEGRAL_PARAM_GETTYPE(This),\
        BOOST_PP_CAT(P, n)\
    >::type BOOST_PP_CAT(V, BOOST_PP_INC(n)); 

#define BOOST_TYPEOF_INTEGRAL_PARAM_DECODE(This, n)\
    typedef decode_integral<BOOST_TYPEOF_INTEGRAL_PARAM_GETTYPE(This), BOOST_PP_CAT(iter, n)> BOOST_PP_CAT(d, n);\
    static const BOOST_TYPEOF_INTEGRAL_PARAM_GETTYPE(This) BOOST_PP_CAT(P, n) = BOOST_PP_CAT(d, n)::value;\
    typedef typename BOOST_PP_CAT(d, n)::iter BOOST_PP_CAT(iter, BOOST_PP_INC(n));

#define BOOST_TYPEOF_INTEGRAL_PARAM_PLACEHOLDER(Param)\
    (BOOST_TYPEOF_INTEGRAL_PARAM_GETTYPE(Param))0

#define BOOST_TYPEOF_INTEGRAL_PARAM_DECLARATION_TYPE(Param)\
    BOOST_TYPEOF_INTEGRAL_PARAM_GETTYPE(Param)

#define BOOST_TYPEOF_INTEGRAL_PARAM_PLACEHOLDER_TYPES(Param, n)\
    BOOST_PP_CAT(T,n)

#define BOOST_TYPEOF_INTEGRAL_PARAM_TT_CATEGORY 1


#endif//BOOST_TYPEOF_COMPLIANT_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED
