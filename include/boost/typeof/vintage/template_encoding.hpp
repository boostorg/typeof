// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_TEMPLATE_ENCODING_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_TEMPLATE_ENCODING_HPP_INCLUDED

#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <boost/typeof/config.hpp>
#include <boost/typeof/vintage/type_to_macro.hpp>
#include <boost/typeof/vintage/encode_decode.hpp>
#include <boost/typeof/vintage/int_encoding.hpp>

//Encoding templates
#define BOOST_TYPEOF_typename_encode(arg) arg
#define BOOST_TYPEOF_integral_encode(arg) encode_integral_wrapper<arg> BOOST_PP_EMPTY()
#define BOOST_TYPEOF_unsigned_integral_encode(arg) encode_unsigned_integral_wrapper<arg> BOOST_PP_EMPTY()

//Decoding templates
#define BOOST_TYPEOF_typename_decode(n,text) \
typedef typename decode_impl<TYPEOF_GET_VALUE(BOOST_PP_CAT(iter,n))>::decoder<TYPEOF_GET_NEXT(BOOST_PP_CAT(iter,n))> BOOST_PP_CAT(decode,n);\
typedef typename BOOST_PP_CAT(decode,n)::type BOOST_PP_CAT(A,n);\
typedef typename BOOST_PP_CAT(decode,n)::iter BOOST_PP_CAT(iter,BOOST_PP_INC(n));

#define BOOST_TYPEOF_integral_decode(n,text) \
typedef decode_integral<BOOST_PP_CAT(iter,n)> BOOST_PP_CAT(decode,n);\
BOOST_STATIC_CONSTANT(text,BOOST_PP_CAT(A,n)=(TYPEOF_GET_VALUE(BOOST_PP_CAT(decode,n))));\
typedef typename BOOST_PP_CAT(decode,n)::iter BOOST_PP_CAT(iter,BOOST_PP_INC(n));

#define BOOST_TYPEOF_unsigned_integral_decode(n,text) \
typedef decode_unsigned_integral<BOOST_PP_CAT(iter,n)> BOOST_PP_CAT(decode,n);\
BOOST_STATIC_CONSTANT(text,BOOST_PP_CAT(A,n)=(BOOST_PP_CAT(decode,n)::value));\
typedef typename BOOST_PP_CAT(decode,n)::iter BOOST_PP_CAT(iter,BOOST_PP_INC(n));


#define BOOST_TYPEOF_ENCODE_SEQ(z,n,seq)\
  BOOST_PP_SEQ_ELEM(n, seq) BOOST_PP_CAT(A,n)

#define BOOST_TYPEOF_STORE_TYPE_START(z,n,seq) type_list<BOOST_TYPEOF_ENCODE_SEQ_ELEMENT(z,n,seq),
#define BOOST_TYPEOF_STORE_TYPE_END(z,n,seq) > BOOST_PP_EMPTY()

#define BOOST_TYPEOF_ENCODE_TEMPLATE(template_type,seq)\
    template<>\
    struct encode_impl<BOOST_TYPEOF_UNIQUE_ID()>\
    {\
        template<typename V, BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(seq),typename A),typename Types>\
        struct encoder {\
            typedef Types BOOST_PP_CAT(types_,BOOST_PP_SEQ_SIZE(seq));\
            BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),BOOST_TYPEOF_PUSH_FRONT,BOOST_PP_SEQ_SIZE(seq))\
            BOOST_STATIC_CONSTANT(int,value =sizeof(BOOST_DEDUCED_TYPENAME encode_modifier<mpl::next<V>::type,BOOST_DEDUCED_TYPENAME types_0::type,types_1>::encoded_type));\
            friend sizer<BOOST_TYPEOF_UNIQUE_ID()> encode_value(const sizer<V::index>&,const sizer<V::pos>&);\
        };\
    };\
    template<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(seq),BOOST_TYPEOF_ENCODE_SEQ,seq),typename V,typename Types>\
    typename encode_impl<BOOST_TYPEOF_UNIQUE_ID()>::encoder<V,BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(seq),BOOST_TYPEOF_ENCODE_SEQ_ELEMENT,seq),Types> encode(template_type<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(seq),A)> const& (*)(V,Types));

#define BOOST_TYPEOF_DECODE_TEMPLATE(template_type,seq)\
    template<>\
    struct decode_impl<BOOST_TYPEOF_UNIQUE_ID()>\
    {\
        template<typename Iter>\
        struct decoder {\
            typedef Iter iter0;\
            BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),BOOST_TYPEOF_DECODE_SEQ_ELEMENT,seq)\
            typedef template_type<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(seq),A)> type;\
            typedef BOOST_PP_CAT(iter,BOOST_PP_SEQ_SIZE(seq)) iter;\
        };\
    };

#define BOOST_TYPEOF_REGISTER_TEMPLATE_X(template_type,seq)\
namespace boost { namespace type_of{\
   BOOST_TYPEOF_ENCODE_TEMPLATE(template_type,seq)\
   BOOST_TYPEOF_DECODE_TEMPLATE(template_type,seq)\
}}//namespace boost::type_of

#endif //BOOST_VINTAGE_TEMPLATE_ENCODING_HPP_INCLUDED
