// Copyright (C) 2004 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_TEMPLATE_ENCODING_HPP_INCLUDED
#define BOOST_TYPEOF_TEMPLATE_ENCODING_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/seq/transform.hpp>

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

// As suggested by Paul Mensonides:

#define BOOST_TYPEOF_TOSEQ(x)\
    BOOST_PP_IIF(\
        BOOST_PP_IS_UNARY(x),\
        x BOOST_PP_TUPLE_EAT(3), BOOST_PP_REPEAT\
    )(x, BOOST_TYPEOF_TOSEQ_2, ~)

#define BOOST_TYPEOF_TOSEQ_2(z, n, _) (class)

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

#endif//BOOST_TYPEOF_TEMPLATE_ENCODING_HPP_INCLUDED
