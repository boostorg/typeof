// Copyright (C) 2004 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_REGISTER_INTEGRAL_HPP_INCLUDED
#define BOOST_TYPEOF_REGISTER_INTEGRAL_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/expand.hpp>

// The template parameter description, entered by the user,
// is converted into a polymorphic "object" 
// that is used to generate the code responsible for
// encoding/decoding the parameter, etc.

// make sure to cat the sequence first, and only then add the prefix.
#define BOOST_TYPEOF_MAKE_OBJ(elem) BOOST_PP_CAT(\
    BOOST_TYPEOF_MAKE_OBJ,\
    BOOST_PP_SEQ_CAT((_) BOOST_TYPEOF_TO_SEQ(elem))\
    )

#define BOOST_TYPEOF_TO_SEQ(tokens) BOOST_TYPEOF_ ## tokens ## _BOOST_TYPEOF 

// BOOST_TYPEOF_REGISTER_TEMPLATE

#define BOOST_TYPEOF_REGISTER_TEMPLATE(Name, Params)\
    BOOST_TYPEOF_REGISTER_TEMPLATE_IMPL(\
        Name,\
        BOOST_TYPEOF_MAKE_OBJS(BOOST_TYPEOF_TOSEQ(Params)),\
        BOOST_PP_SEQ_SIZE(BOOST_TYPEOF_TOSEQ(Params)),\
        BOOST_TYPEOF_UNIQUE_ID())\

#define BOOST_TYPEOF_OBJECT_MAKER(s, data, elem)\
    BOOST_TYPEOF_MAKE_OBJ(elem)

#define BOOST_TYPEOF_MAKE_OBJS(Params)\
    BOOST_PP_SEQ_TRANSFORM(BOOST_TYPEOF_OBJECT_MAKER, ~, Params)

#define BOOST_TYPEOF_TOSEQ(x)\
    BOOST_PP_SEQ_CAT(\
        (BOOST_TYPEOF_STEP3)\
        (BOOST_PP_CAT(BOOST_TYPEOF_STEP2, BOOST_PP_EXPAND(BOOST_TYPEOF_STEP1 x)))\
    )

#define BOOST_TYPEOF_STEP1(x) _(x)
#define BOOST_TYPEOF_STEP2BOOST_TYPEOF_STEP1
#define BOOST_TYPEOF_STEP3BOOST_TYPEOF_STEP2_

#define BOOST_TYPEOF_STEP31 (class)
#define BOOST_TYPEOF_STEP32 BOOST_TYPEOF_STEP31(class)
#define BOOST_TYPEOF_STEP33 BOOST_TYPEOF_STEP32(class)
#define BOOST_TYPEOF_STEP34 BOOST_TYPEOF_STEP33(class)
#define BOOST_TYPEOF_STEP35 BOOST_TYPEOF_STEP34(class)
#define BOOST_TYPEOF_STEP36 BOOST_TYPEOF_STEP35(class)
#define BOOST_TYPEOF_STEP37 BOOST_TYPEOF_STEP36(class)
#define BOOST_TYPEOF_STEP38 BOOST_TYPEOF_STEP37(class)
#define BOOST_TYPEOF_STEP39 BOOST_TYPEOF_STEP38(class)
#define BOOST_TYPEOF_STEP310 BOOST_TYPEOF_STEP39(class)
#define BOOST_TYPEOF_STEP311 BOOST_TYPEOF_STEP310(class)
#define BOOST_TYPEOF_STEP312 BOOST_TYPEOF_STEP311(class)
#define BOOST_TYPEOF_STEP313 BOOST_TYPEOF_STEP312(class)
#define BOOST_TYPEOF_STEP314 BOOST_TYPEOF_STEP313(class)
#define BOOST_TYPEOF_STEP315 BOOST_TYPEOF_STEP314(class)
#define BOOST_TYPEOF_STEP316 BOOST_TYPEOF_STEP315(class)
#define BOOST_TYPEOF_STEP317 BOOST_TYPEOF_STEP316(class)
#define BOOST_TYPEOF_STEP318 BOOST_TYPEOF_STEP317(class)
#define BOOST_TYPEOF_STEP319 BOOST_TYPEOF_STEP318(class)
#define BOOST_TYPEOF_STEP320 BOOST_TYPEOF_STEP319(class)

// "interface"

#define BOOST_TYPEOF_PARAM_EXPAND_TYPE(Param)\
    BOOST_PP_CAT(BOOST_TYPEOF_PARAM_EXPAND_, BOOST_PP_SEQ_ELEM(0, Param))(Param)

// BOOST_TYPEOF_VIRTUAL

#define BOOST_TYPEOF_CAT_4(a, b, c, d) BOOST_TYPEOF_CAT_4_I(a, b, c, d)
#define BOOST_TYPEOF_CAT_4_I(a, b, c, d) a ## b ## c ## d

#define BOOST_TYPEOF_VIRTUAL(Fun, Obj)\
    BOOST_TYPEOF_CAT_4(BOOST_TYPEOF_, BOOST_PP_SEQ_HEAD(Obj), _, Fun)

// BOOST_TYPEOF_SEQ_ENUM[_TRAILING][_1]
// Two versions provided due to reentrancy issue

#define BOOST_TYPEOF_SEQ_EXPAND_ELEMENT(z,n,seq)\
   BOOST_PP_SEQ_ELEM(0,seq) (z,n,BOOST_PP_SEQ_ELEM(n,BOOST_PP_SEQ_ELEM(1,seq)))

#define BOOST_TYPEOF_SEQ_ENUM(seq,macro)\
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(seq),BOOST_TYPEOF_SEQ_EXPAND_ELEMENT,(macro)(seq))

#define BOOST_TYPEOF_SEQ_ENUM_TRAILING(seq,macro)\
    BOOST_PP_ENUM_TRAILING(BOOST_PP_SEQ_SIZE(seq),BOOST_TYPEOF_SEQ_EXPAND_ELEMENT,(macro)(seq))

#define BOOST_TYPEOF_SEQ_EXPAND_ELEMENT_1(z,n,seq)\
    BOOST_PP_SEQ_ELEM(0,seq) (z,n,BOOST_PP_SEQ_ELEM(n,BOOST_PP_SEQ_ELEM(1,seq)))

#define BOOST_TYPEOF_SEQ_ENUM_1(seq,macro)\
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(seq),BOOST_TYPEOF_SEQ_EXPAND_ELEMENT_1,(macro)(seq))

#define BOOST_TYPEOF_SEQ_ENUM_TRAILING_1(seq,macro)\
    BOOST_PP_ENUM_TRAILING(BOOST_PP_SEQ_SIZE(seq),BOOST_TYPEOF_SEQ_EXPAND_ELEMENT_1,(macro)(seq))

#endif//BOOST_TYPEOF_COMPLIANT_TEMPLATE_ENCODING_HPP_INCLUDED
