// Copyright (C) 2005 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_TYPE_TEMPLATE_PARAM_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_TYPE_TEMPLATE_PARAM_HPP_INCLUDED

#include <boost/typeof/type_template_param.hpp>

// TYPE_PARAM "virtual functions" implementation

#define BOOST_TYPEOF_TYPE_PARAM_ENCODE(This, n)\
    typedef typename encode_type<\
        BOOST_PP_CAT(V, n),\
        BOOST_PP_CAT(P, n)\
    >::type BOOST_PP_CAT(V, BOOST_PP_INC(n)); 

#define BOOST_TYPEOF_TYPE_PARAM_DECODE(This, n)\
    typedef decode_type< BOOST_PP_CAT(iter, n) > BOOST_PP_CAT(d, n);\
    typedef typename BOOST_PP_CAT(d, n)::type BOOST_PP_CAT(P, n);\
    typedef typename BOOST_PP_CAT(d, n)::iter BOOST_PP_CAT(iter, BOOST_PP_INC(n));

#define BOOST_TYPEOF_TYPE_PARAM_PLACEHOLDER(Param) int
#define BOOST_TYPEOF_TYPE_PARAM_DECLARATION_TYPE(Param) class
#define BOOST_TYPEOF_TYPE_PARAM_PLACEHOLDER_TYPES(Param, n) BOOST_PP_CAT(T,n)
#define BOOST_TYPEOF_TYPE_PARAM_ISTEMPLATE 0

#endif//BOOST_TYPEOF_COMPLIANT_TYPE_TEMPLATE_PARAM_HPP_INCLUDED
