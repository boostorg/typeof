// Copyright (C) 2004 Arkadiy Vertleyb
// Copyright (C) 2005 Peder Holt 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_TEMPLATE_ENCODING_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_TEMPLATE_ENCODING_HPP_INCLUDED

#include <boost/typeof/compliant/encode_decode.hpp>
#include <boost/typeof/compliant/int_encoding.hpp>

#include <boost/typeof/template_encoding.hpp>

#include <boost/typeof/compliant/type_template_param.hpp>
#include <boost/typeof/compliant/integral_template_param.hpp>
#include <boost/typeof/compliant/template_template_param.hpp>

#include <boost/preprocessor/seq/for_each_i.hpp>

#define BOOST_TYPEOF_PLACEHOLDER(z, n, elem)\
    BOOST_TYPEOF_VIRTUAL(PLACEHOLDER, elem)(elem)

#define BOOST_TYPEOF_PLACEHOLDER_TYPES(z, n, elem)\
    BOOST_TYPEOF_VIRTUAL(PLACEHOLDER_TYPES, elem)(elem, n)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_PARAM(r, data, n, elem)\
    BOOST_TYPEOF_VIRTUAL(ENCODE, elem)(elem, n)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_PARAM(r, data, n, elem)\
    BOOST_TYPEOF_VIRTUAL(DECODE, elem)(elem, n)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR(z, n, elem) \
    BOOST_TYPEOF_VIRTUAL(EXPANDTYPE, elem)(elem) BOOST_PP_CAT(P, n)

#define BOOST_TYPEOF_REGISTER_DEFAULT_TEMPLATE_TYPE(Name,Params,ID)\
    Name< BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Params), P) >

//Since we are creating an internal decode struct, we need to use different template names, T instead of P.
#define BOOST_TYPEOF_REGISTER_DECODER_TYPE_PARAM_PAIR(z,n,elem) \
    BOOST_TYPEOF_VIRTUAL(EXPANDTYPE, elem)(elem) BOOST_PP_CAT(T, n)

//Default template param decoding
#define BOOST_TYPEOF_TYPEDEF_DECODED_TEMPLATE_TYPE(Name,Params)\
    typedef Name<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Params),P)> type;        

//Branch the decoding
#define BOOST_TYPEOF_TYPEDEF_DECODED_TYPE(Name,Params)\
    BOOST_PP_IF(BOOST_TYPEOF_HAS_TEMPLATES(Params),\
        BOOST_TYPEOF_TYPEDEF_DECODED_TEMPLATE_TEMPLATE_TYPE,\
        BOOST_TYPEOF_TYPEDEF_DECODED_TEMPLATE_TYPE)(Name,Params)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_IMPL(Name, Params, Size, ID)\
    namespace boost{namespace type_of{namespace{\
    BOOST_TYPEOF_REGISTER_TEMPLATE_TEMPLATE_IMPL(Name, Params, ID)\
    template<class V\
        BOOST_TYPEOF_SEQ_ENUM_TRAILING(Params, BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR)\
    >\
    struct encode_type_impl<V, Name<BOOST_PP_ENUM_PARAMS(Size, P)> >\
    {\
        typedef typename BOOST_TYPEOF_PUSH_BACK<V, boost::mpl::size_t<ID> >::type V0;\
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_PARAM, ~, Params)\
        typedef BOOST_PP_CAT(V, Size) type;\
    };\
    template<class Iter>\
    struct decode_type_impl<boost::mpl::size_t<ID>, Iter>\
    {\
        typedef Iter iter0;\
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_PARAM, ~, Params)\
        BOOST_TYPEOF_TYPEDEF_DECODED_TYPE(Name, Params)\
        typedef BOOST_PP_CAT(iter, Size) iter;\
    };\
    }}}

#endif//BOOST_TYPEOF_COMPLIANT_TEMPLATE_ENCODING_HPP_INCLUDED
