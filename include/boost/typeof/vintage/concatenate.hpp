// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_CONCATENATE_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_CONCATENATE_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/typeof/vintage/type_list.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#include <boost/preprocessor/repetition/repeat.hpp>
// Assumes iter0 contains initial iterator

#define BOOST_TYPEOF_DECODE_PARAM(z, n, text)   \
    typedef decode_impl<TYPEOF_GET_VALUE(iter##n)>::decoder<TYPEOF_GET_NEXT(iter##n)> decode##n;\
    typedef typename decode##n::type P##n;      \
    typedef typename decode##n::iter BOOST_PP_CAT(iter, BOOST_PP_INC(n));

#define BOOST_TYPEOF_DECODE_PARAMS(n)\
    BOOST_PP_REPEAT(n, BOOST_TYPEOF_DECODE_PARAM, _);

#define BOOST_TYPEOF_PUSH_FRONT(z,n,template_size)\
  typedef type_list<\
        BOOST_PP_CAT(P,BOOST_PP_DEC(BOOST_PP_SUB(template_size,n))),\
        BOOST_PP_CAT(types_,BOOST_PP_SUB(template_size,n))\
    > BOOST_PP_CAT(types_,BOOST_PP_DEC(BOOST_PP_SUB(template_size,n)));

#endif//BOOST_TYPEOF_CONCATENATE_HPP_INCLUDED
