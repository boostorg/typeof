// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_TEMPLATE_ENCODING_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_TEMPLATE_ENCODING_HPP_INCLUDED

#include <boost/typeof/compliant/encode_decode.hpp>
#include <boost/typeof/compliant/int_encoding.hpp>
#include <boost/typeof/register_integral.hpp>

//////////

// TYPE_PARAM "virtual functions" implementation

#define BOOST_TYPEOF_ENCODE_TYPE_PARAM(This, n)\
    typedef typename encode_type<\
        BOOST_PP_CAT(V, n),\
        BOOST_PP_CAT(P, n)\
    >::type BOOST_PP_CAT(V, BOOST_PP_INC(n)); 

#define BOOST_TYPEOF_DECODE_TYPE_PARAM(This, n)\
    typedef decode_type< BOOST_PP_CAT(iter, n) > BOOST_PP_CAT(d, n);\
    typedef typename BOOST_PP_CAT(d, n)::type BOOST_PP_CAT(P, n);\
    typedef typename BOOST_PP_CAT(d, n)::iter BOOST_PP_CAT(iter, BOOST_PP_INC(n));

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

// "function objects"

#define BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_PARAM(r, data, n, elem)\
    BOOST_TYPEOF_PARAM_ENCODE(BOOST_TYPEOF_MAKE_OBJ(elem))(BOOST_TYPEOF_MAKE_OBJ(elem), n)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_PARAM(r, data, n, elem)\
    BOOST_TYPEOF_PARAM_DECODE(BOOST_TYPEOF_MAKE_OBJ(elem))(BOOST_TYPEOF_MAKE_OBJ(elem), n)

#define BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR(r, data, n, elem)\
    , BOOST_TYPEOF_PARAM_GETTYPE(BOOST_TYPEOF_MAKE_OBJ(elem)) BOOST_PP_CAT(P, n)

//

#define BOOST_TYPEOF_REGISTER_TEMPLATE_X_IMPL(Name, Params, ID)\
    namespace boost{namespace type_of{namespace{\
    template<class V\
        BOOST_PP_SEQ_FOR_EACH_I(\
            BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR,\
            ~,\
            Params)\
    >\
    struct encode_type_impl<V, Name<\
        BOOST_PP_ENUM_PARAMS(\
        BOOST_PP_SEQ_SIZE(Params),\
        P)> >\
    {\
        typedef typename BOOST_TYPEOF_PUSH_BACK<V, boost::mpl::size_t<ID> >::type V0;\
        BOOST_PP_SEQ_FOR_EACH_I(\
            BOOST_TYPEOF_REGISTER_TEMPLATE_ENCODE_PARAM,\
            ~,\
            Params)\
        typedef BOOST_PP_CAT(V, BOOST_PP_SEQ_SIZE(Params)) type;\
    };\
    template<class Iter>\
    struct decode_type_impl<boost::mpl::size_t<ID>, Iter>\
    {\
        typedef Iter iter0;\
        BOOST_PP_SEQ_FOR_EACH_I(\
            BOOST_TYPEOF_REGISTER_TEMPLATE_DECODE_PARAM,\
            ~,\
            Params)\
        typedef Name< BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Params), P) > type;\
        typedef BOOST_PP_CAT(iter, BOOST_PP_SEQ_SIZE(Params)) iter;\
    };\
    }}}

#define BOOST_TYPEOF_REGISTER_TEMPLATE_X(Name, Params)\
    BOOST_TYPEOF_REGISTER_TEMPLATE_X_IMPL(Name, Params, BOOST_TYPEOF_UNIQUE_ID())

#endif//BOOST_TYPEOF_COMPLIANT_TEMPLATE_ENCODING_HPP_INCLUDED
