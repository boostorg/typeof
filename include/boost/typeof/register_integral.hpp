// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_REGISTER_INTEGRAL_HPP_INCLUDED
#define BOOST_TYPEOF_REGISTER_INTEGRAL_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>

//////////

#define BOOST_TYPEOF_REGISTER_TEMPLATE_class_ BOOST_TYPEOF_REGISTER_TEMPLATE_typename_
#define BOOST_TYPEOF_REGISTER_TEMPLATE_typename_        (typename)(TYPE)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_integral(x)      (x)(VALUE)

//////////

#define BOOST_TYPEOF_REGISTER_TEMPLATE_char_     BOOST_TYPEOF_REGISTER_TEMPLATE_integral(char)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_short_    BOOST_TYPEOF_REGISTER_TEMPLATE_integral(short)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_int_      BOOST_TYPEOF_REGISTER_TEMPLATE_integral(int)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_long_     BOOST_TYPEOF_REGISTER_TEMPLATE_integral(long)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_bool_     BOOST_TYPEOF_REGISTER_TEMPLATE_integral(bool)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_unsigned_ BOOST_TYPEOF_REGISTER_TEMPLATE_integral(unsigned)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_size_t_   BOOST_TYPEOF_REGISTER_TEMPLATE_integral(size_t)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_unsignedchar     BOOST_TYPEOF_REGISTER_TEMPLATE_integral(unsigned char)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_unsignedshort    BOOST_TYPEOF_REGISTER_TEMPLATE_integral(unsigned short)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_unsignedint      BOOST_TYPEOF_REGISTER_TEMPLATE_integral(unsigned int)
#define BOOST_TYPEOF_REGISTER_TEMPLATE_unsignedlong     BOOST_TYPEOF_REGISTER_TEMPLATE_integral(unsigned long)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_signedchar     BOOST_TYPEOF_REGISTER_TEMPLATE_integral(signed char)

//////////

#define BOOST_TYPEOF_TO_SEQ(tokens) BOOST_TYPEOF_ ## tokens ## _BOOST_TYPEOF 

#define BOOST_TYPEOF_unsigned (unsigned)
#define BOOST_TYPEOF_signed (signed)

#define BOOST_TYPEOF_char_BOOST_TYPEOF (char)(_)
#define BOOST_TYPEOF_short_BOOST_TYPEOF (short)(_)
#define BOOST_TYPEOF_int_BOOST_TYPEOF (int)(_)
#define BOOST_TYPEOF_long_BOOST_TYPEOF (long)(_)
#define BOOST_TYPEOF_bool_BOOST_TYPEOF (bool)(_)
#define BOOST_TYPEOF_class_BOOST_TYPEOF (class)(_)
#define BOOST_TYPEOF_typename_BOOST_TYPEOF (typename)(_)
#define BOOST_TYPEOF_unsigned_BOOST_TYPEOF (unsigned)(_)
#define BOOST_TYPEOF_size_t_BOOST_TYPEOF (size_t)(_)

#define char_BOOST_TYPEOF (char)
#define short_BOOST_TYPEOF (short)
#define int_BOOST_TYPEOF (int)
#define long_BOOST_TYPEOF (long)

#define EAT_SPACE(tokens) BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, BOOST_TYPEOF_TO_SEQ(tokens)), BOOST_PP_SEQ_ELEM(1, BOOST_TYPEOF_TO_SEQ(tokens)))

///////////

#define BOOST_TYPEOF_INTEGRAL(X) REGISTER_TEMPLATE_INTEGRAL(X) BOOST_TYPEOF_EAT
#define BOOST_TYPEOF_EAT_BOOST_TYPEOF
#define BOOST_TYPEOF_REGISTER_TEMPLATE_INTEGRAL(X) (inte)(gral(X))

///////////

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_DESCR(n, Params)\
    BOOST_PP_CAT(BOOST_TYPEOF_REGISTER_TEMPLATE_, EAT_SPACE(BOOST_PP_SEQ_ELEM(n, Params)))

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_TYPE(n, Params)\
    BOOST_PP_SEQ_ELEM(0, BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_DESCR(n, Params))

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_SUFFIX(n, Params)\
    BOOST_PP_SEQ_ELEM(1, BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_DESCR(n, Params))

//////////

#define BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_PARAM(z, n, Params)\
    BOOST_PP_CAT(\
        BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_,\
        BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_SUFFIX(n, Params)\
    )(n, Params)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_PARAM(z, n, Params)\
    BOOST_PP_CAT(\
        BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_,\
        BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_SUFFIX(n, Params)\
    )(n, Params)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR(z, n, Params)\
    BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_TYPE(n, Params) BOOST_PP_CAT(P, n)

//////////

#endif//BOOST_TYPEOF_COMPLIANT_TEMPLATE_ENCODING_HPP_INCLUDED
