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
#include <boost/typeof/vintage/encode_decode.hpp>
#include <boost/typeof/vintage/int_encoding.hpp>
#include <boost/typeof/register_integral.hpp>

#define BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_TYPE(n, Params)\
    BOOST_PP_CAT(P, n)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_VALUE(n, Params)\
    integral_wrapper<\
        BOOST_PP_CAT(P, n)\
    >

#define BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_TYPE(n, PARAMS)\
    typedef typename decode_impl<TYPEOF_GET_VALUE(BOOST_PP_CAT(iter,n))>::\
        decoder<TYPEOF_GET_NEXT(BOOST_PP_CAT(iter,n))> BOOST_PP_CAT(d,n);\
    typedef typename BOOST_PP_CAT(d,n)::type BOOST_PP_CAT(P,n);\
    typedef typename BOOST_PP_CAT(d,n)::iter BOOST_PP_CAT(iter,BOOST_PP_INC(n));

#define BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_VALUE(n, Params)\
    typedef decode_integral<BOOST_PP_CAT(iter,n)> BOOST_PP_CAT(d,n);\
    BOOST_STATIC_CONSTANT(BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_TYPE(n, Params),BOOST_PP_CAT(P,n)=(TYPEOF_GET_VALUE(BOOST_PP_CAT(d,n))));\
    typedef typename BOOST_PP_CAT(d,n)::iter BOOST_PP_CAT(iter,BOOST_PP_INC(n));

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_CAST_VALUE(n,Params)\
    BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_TYPE(n, Params)(BOOST_PP_CAT(P,n))

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_CAST_TYPE(n,Params)\
    BOOST_PP_CAT(P,n)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_CAST(z, n, Params)\
    BOOST_PP_CAT(\
        BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_CAST_,\
        BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_SUFFIX(n, Params)\
    )(n, Params)

#define BOOST_TYPEOF_ENCODE_TEMPLATE_X_IMPL(Name, Params, ID)\
    template<>\
    struct encode_impl<ID>\
    {\
        template<typename V, BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Params),typename P),typename Types>\
        struct encoder {\
            typedef Types BOOST_PP_CAT(types_,BOOST_PP_SEQ_SIZE(Params));\
            BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(Params),BOOST_TYPEOF_PUSH_FRONT,BOOST_PP_SEQ_SIZE(Params))\
            BOOST_STATIC_CONSTANT(int,value =sizeof(BOOST_DEDUCED_TYPENAME encode_modifier<mpl::next<V>::type,BOOST_DEDUCED_TYPENAME types_0::type,types_1>::encoded_type));\
            friend sizer<ID> encode_value(const sizer<V::index>&,const sizer<V::pos>&);\
        };\
    };\
    template<\
        BOOST_PP_ENUM(\
            BOOST_PP_SEQ_SIZE(Params),\
            BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR,\
            Params\
        ),typename V,typename Types>\
    typename encode_impl<ID>::\
        encoder<\
            V,\
            BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Params),BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_PARAM,Params),\
            Types\
        > encode(Name<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Params),P)> const& (*)(V,Types));

#define BOOST_TYPEOF_DECODE_TEMPLATE_X_IMPL(Name, Params, ID)\
    template<>\
    struct decode_impl<ID>\
    {\
        template<typename Iter>\
        struct decoder {\
            typedef Iter iter0;\
            BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(Params),BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_PARAM,Params)\
            typedef Name<BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Params),BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_CAST,Params)> type;\
            typedef BOOST_PP_CAT(iter,BOOST_PP_SEQ_SIZE(Params)) iter;\
        };\
    };

#define BOOST_TYPEOF_REGISTER_TEMPLATE_X(template_type,seq)\
namespace boost { namespace type_of{\
   BOOST_TYPEOF_ENCODE_TEMPLATE_X_IMPL(template_type,seq,BOOST_TYPEOF_UNIQUE_ID())\
   BOOST_TYPEOF_DECODE_TEMPLATE_X_IMPL(template_type,seq,BOOST_TYPEOF_UNIQUE_ID())\
}}//namespace boost::type_of

#endif //BOOST_VINTAGE_TEMPLATE_ENCODING_HPP_INCLUDED
