// Copyright (C) 2005 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED

#include <boost/typeof/integral_template_param.hpp>

// INTEGRAL_PARAM "virtual functions" implementation

#define BOOST_TYPEOF_ENCODE_INTEGRAL_PARAM(This, n)\
    typedef typename encode_integral<\
        BOOST_PP_CAT(V, n),\
        BOOST_TYPEOF_PARAM_GETTYPE(This),\
        BOOST_PP_CAT(P, n)\
    >::type BOOST_PP_CAT(V, BOOST_PP_INC(n)); 

#define BOOST_TYPEOF_DECODE_INTEGRAL_PARAM(This, n)\
    typedef decode_integral<BOOST_TYPEOF_PARAM_GETTYPE(This), BOOST_PP_CAT(iter, n)> BOOST_PP_CAT(d, n);\
    static const BOOST_TYPEOF_PARAM_GETTYPE(This) BOOST_PP_CAT(P, n) = BOOST_PP_CAT(d, n)::value;\
    typedef typename BOOST_PP_CAT(d, n)::iter BOOST_PP_CAT(iter, BOOST_PP_INC(n));


#endif//BOOST_TYPEOF_COMPLIANT_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED
