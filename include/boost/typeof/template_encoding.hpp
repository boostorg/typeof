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


// "interface"

#define BOOST_TYPEOF_PARAM_EXPAND_TYPE(Param)\
    BOOST_PP_CAT(BOOST_TYPEOF_PARAM_EXPAND_, BOOST_PP_SEQ_ELEM(0, Param))(Param)


//
#define BOOST_TYPEOF_CAT_4(a, b, c, d) BOOST_TYPEOF_CAT_4_I(a, b, c, d)
#define BOOST_TYPEOF_CAT_4_I(a, b, c, d) a ## b ## c ## d

#define BOOST_TYPEOF_VIRTUAL(Fun, Obj)\
    BOOST_TYPEOF_CAT_4(BOOST_TYPEOF_, BOOST_PP_SEQ_ELEM(0, Obj), _, Fun)
//

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
