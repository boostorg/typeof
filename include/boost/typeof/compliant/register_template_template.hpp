// Copyright (C) 2005 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_REGISTER_TEMPLATE_TEMPLATE_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_REGISTER_TEMPLATE_TEMPLATE_HPP_INCLUDED

#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

namespace boost{namespace type_of {namespace {
    template<class T,class Iter>
    struct decode_template_impl;

    template<class Iter> struct decode_template
        : decode_template_impl<typename mpl::deref<Iter>::type, typename mpl::next<Iter>::type>
    {};
}}}

#define BOOST_TYPEOF_MAKE_OBJ_template(x)   BOOST_TYPEOF_TEMPLATE_PARAM(x)
#define BOOST_TYPEOF_TEMPLATE(X) template(X) BOOST_TYPEOF_EAT
#define BOOST_TYPEOF_template(X) (template(X))

#define BOOST_TYPEOF_TEMPLATE_PARAM(Type)\
    (TEMPLATE_PARAM)\
    (Type)\
    (class)

#define BOOST_TYPEOF_ENCODE_TEMPLATE_PARAM(This, n)\
   typedef typename BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME(encode_template,This)<\
       BOOST_PP_CAT(V, n),\
       BOOST_PP_CAT(P, n)\
   >::type BOOST_PP_CAT(V, BOOST_PP_INC(n));

#define BOOST_TYPEOF_DECODE_TEMPLATE_PARAM(This, n)\
   typedef decode_template< BOOST_PP_CAT(iter, n) > BOOST_PP_CAT(d, n);\
   typedef typename BOOST_PP_CAT(d, n)::type BOOST_PP_CAT(P, n);\
   typedef typename BOOST_PP_CAT(d, n)::iter BOOST_PP_CAT(iter,BOOST_PP_INC(n));

//In order to handle template template arguments correctly, we need to expand
//e.g (typename)(typename) to template <typename,typename> class.
#define BOOST_TYPEOF_EXPAND_TEMPLATE_PARAM(Param)\
    template<BOOST_TYPEOF_EXPAND_TEMPLATE_PARAM_IMPL(BOOST_TYPEOF_PARAM_GETTYPE(Param))> class

#define BOOST_TYPEOF_EXPAND_TEMPLATE_PARAM_IMPL(Param)\
    BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Param),BOOST_TYPEOF_EXPAND_TEMPLATE_ELEMENT,Param)

#define BOOST_TYPEOF_EXPAND_TEMPLATE_ELEMENT(z,n,Param) BOOST_PP_SEQ_ELEM(n, Param)

//This is used during decode of template template arguments, tt arguments are wrapped inside encode_template_...
//and the decode_template_... must define a class PN for these arguments.
#define BOOST_TYPEOF_COMPACT_TEMPLATE_PARAM(Param) class
#define BOOST_TYPEOF_COMPACT_TYPE_PARAM(Param) BOOST_TYPEOF_PARAM_GETTYPE(Param)
#define BOOST_TYPEOF_COMPACT_INTEGRAL_PARAM(Param) BOOST_TYPEOF_PARAM_GETTYPE(Param)
#define BOOST_TYPEOF_COMPACT_EXPLICIT_INTEGRAL_PARAM(Param) BOOST_TYPEOF_PARAM_GETTYPE(Param)

#define BOOST_TYPEOF_COMPACT_TYPE(Param)\
    BOOST_PP_CAT(BOOST_TYPEOF_COMPACT_, BOOST_PP_SEQ_ELEM(0, Param))(Param)

//Again, decode_template_... specializations must expand to encode_template_...<boost::mpl::vector0,Pn>.
#define BOOST_TYPEOF_WRAPPED_TEMPLATE_PARAM(n,Param) BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME(encode_template,Param)<boost::mpl::vector0<>,BOOST_PP_CAT(P,n)>
#define BOOST_TYPEOF_WRAPPED_TYPE_PARAM(n,Param) BOOST_PP_CAT(P,n)
#define BOOST_TYPEOF_WRAPPED_INTEGRAL_PARAM(n,Param) BOOST_PP_CAT(P,n)
#define BOOST_TYPEOF_WRAPPED_EXPLICIT_INTEGRAL_PARAM(n,Param) BOOST_PP_CAT(P,n)

#define BOOST_TYPEOF_WRAPPED_TYPE_IMPL(n,Param)\
    BOOST_PP_CAT(BOOST_TYPEOF_WRAPPED_, BOOST_PP_SEQ_ELEM(0, Param))(n,Param)

#define BOOST_TYPEOF_WRAPPED_TYPE(z,n,Params)\
    BOOST_TYPEOF_WRAPPED_TYPE_IMPL(n,BOOST_TYPEOF_MAKE_OBJ(BOOST_PP_SEQ_ELEM(n, Params)))


//We need to generate a unique name for template template registration:  
#define BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME(prefix,Params)\
    BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME_IMPL(prefix,BOOST_TYPEOF_PARAM_GETTYPE(Params))

#define BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME_IMPL(prefix,Params)\
    BOOST_PP_SEQ_FOLD_LEFT(\
        BOOST_TYPEOF_TEMPLATE_TEMPLATE_CAT,\
        BOOST_PP_SEQ_HEAD((prefix)Params),\
        BOOST_PP_SEQ_TAIL((prefix)Params)\
    )

#define BOOST_TYPEOF_TEMPLATE_TEMPLATE_CAT(s,state,x)\
    BOOST_PP_SEQ_CAT((state)(_)(BOOST_TYPEOF_PARAM_GETNAME(BOOST_TYPEOF_MAKE_OBJ(x))))    

//Category: Can this parameter be used in a template template class?
//0 -> Not supported
//1 -> Simple type
//2 -> Template template type (can not be used to create template template template types :)
#define BOOST_TYPEOF_PARAM_TT_CATEGORY(Param) \
    BOOST_PP_CAT(BOOST_TYPEOF_TT_CATEGORY_,BOOST_PP_SEQ_ELEM(0, Param))
#define BOOST_TYPEOF_TT_CATEGORY_INTEGRAL_PARAM 1
#define BOOST_TYPEOF_TT_CATEGORY_TYPE_PARAM 1
#define BOOST_TYPEOF_TT_CATEGORY_EXPLICIT_INTEGRAL_PARAM 0
#define BOOST_TYPEOF_TT_CATEGORY_TEMPLATE_PARAM 2

#define BOOST_TYPEOF_CHECK_TT_CATEGORY(s, data, elem)\
    BOOST_PP_EQUAL(BOOST_TYPEOF_PARAM_TT_CATEGORY(BOOST_TYPEOF_MAKE_OBJ(elem)), data)
//BOOST_TYPEOF_PARAM_TT_CATEGORY(BOOST_TYPEOF_MAKE_OBJ(elem))
//Test if the current template arguments support template template encoding
#define BOOST_TYPEOF_SUPPORT_TEMPLATE_TEMPLATE_ENCODING(Params)\
    BOOST_PP_EQUAL(\
        BOOST_PP_DEC(\
            BOOST_PP_SEQ_SIZE(\
                (_)BOOST_PP_SEQ_FILTER(BOOST_TYPEOF_CHECK_TT_CATEGORY,1,Params)\
            )\
        ),\
        BOOST_PP_SEQ_SIZE(Params)\
    )

//Check if one of the arguments is a template template argument.
#define BOOST_TYPEOF_HAS_TEMPLATE_TEMPLATE_ARGUMENTS(Params)\
    BOOST_PP_NOT_EQUAL(\
        BOOST_PP_SEQ_SIZE(\
            (_)BOOST_PP_SEQ_FILTER(BOOST_TYPEOF_CHECK_TT_CATEGORY,2,Params)\
        ),\
        1\
    )

//Return the sequence of template template arguments
#define BOOST_TYPEOF_GET_TEMPLATE_TEMPLATE_SEQUENCES(Params)\
    BOOST_PP_SEQ_FILTER(BOOST_TYPEOF_CHECK_TT_CATEGORY,2,Params)

//Define template template arguments
#define BOOST_TYPEOF_REGISTER_TEMPLATE_TEMPLATE_IMPL(Name,Params,ID)\
    BOOST_PP_IF(BOOST_TYPEOF_SUPPORT_TEMPLATE_TEMPLATE_ENCODING(Params),\
        BOOST_TYPEOF_REGISTER_THIS_FOR_TT_ENCODING,\
        BOOST_TYPEOF_REGISTER_ARGUMENTS_FOR_TT_ENCODING)(Name,Params,ID)


//Define template template params
#define BOOST_TYPEOF_REGISTER_THIS_FOR_TT_ENCODING(Name,Params,ID)\
    template<typename V,BOOST_TYPEOF_EXPAND_TYPE(BOOST_TYPEOF_TEMPLATE_PARAM(Params)) T>\
    struct BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME_IMPL(encode_template,Params);\
    template<typename V>\
    struct BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME_IMPL(encode_template,Params)<V,Name>\
    : BOOST_TYPEOF_PUSH_BACK<V, mpl::size_t<ID> >\
    {};\
    template<class Iter> struct decode_template_impl<mpl::size_t<ID>, Iter> \
    {\
        typedef BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME_IMPL(encode_template,Params)<\
            boost::mpl::vector0<>,\
            Name\
        > type;\
        typedef Iter iter;\
    };   

//Check if one of the arguments needs to be predeclared
#define BOOST_TYPEOF_REGISTER_ARGUMENTS_FOR_TT_ENCODING(Name,Params,ID)\
    BOOST_TYPEOF_DEFINE_TEMPLATE_TEMPLATE_ARGUMENTS(Name,Params,ID,(_)BOOST_TYPEOF_GET_TEMPLATE_TEMPLATE_SEQUENCES(Params))

#define BOOST_TYPEOF_DEFINE_TEMPLATE_TEMPLATE_ARGUMENTS(Name,Params,ID,TTParams)\
    BOOST_PP_CAT(\
        BOOST_TYPEOF_DEFINE_TEMPLATE_TEMPLATE_ARGUMENTS_,\
        BOOST_PP_NOT_EQUAL(BOOST_PP_SEQ_SIZE(TTParams),1)\
    )(Name,Params,ID,TTParams)

#define BOOST_TYPEOF_DEFINE_TEMPLATE_TEMPLATE_ARGUMENTS_0(Name,Params,ID,TTParams)\

//We have template template arguments, we need to implement a special decoding for this.
#define BOOST_TYPEOF_DEFINE_TEMPLATE_TEMPLATE_ARGUMENTS_1(Name,Params,ID,TTParams)\
    BOOST_PP_SEQ_FOR_EACH(BOOST_TYPEOF_DEFINE_TEMPLATE_TEMPLATE_ARGUMENT,_,BOOST_PP_SEQ_POP_FRONT(TTParams))\
    template<typename T\
        BOOST_TYPEOF_SEQ_ENUM_TRAILING(Params,BOOST_TYPEOF_REGISTER_COMPACT_TEMPLATE_PARAM_PAIR)\
    >\
    struct BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME_IMPL(decode_template,Params);\
    template<\
        BOOST_TYPEOF_SEQ_ENUM(Params,BOOST_TYPEOF_REGISTER_TEMPLATE_PARAM_PAIR)\
    >\
    struct BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME_IMPL(decode_template,Params)<\
    boost::mpl::size_t<ID> BOOST_PP_ENUM_TRAILING(\
        BOOST_PP_SEQ_SIZE(Params),\
        BOOST_TYPEOF_WRAPPED_TYPE,\
        Params\
    ) > {\
        typedef Name< BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Params), P) > type;\
    };

//Make the signature for this template template argument available.
#define BOOST_TYPEOF_DEFINE_TEMPLATE_TEMPLATE_ARGUMENT(r,data,elem)\
    template<typename V,BOOST_TYPEOF_EXPAND_TYPE(BOOST_TYPEOF_MAKE_OBJ(elem)) T>\
    struct BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME(encode_template,BOOST_TYPEOF_MAKE_OBJ(elem));

//This typedef is used inside decode_type_impl as a replacement for typedef Name<P0,P1,...PN> type;
#define BOOST_TYPEOF_REGISTER_TEMPLATE_TEMPLATE_TYPE(Name,Params,ID)\
    typename BOOST_TYPEOF_TEMPLATE_TEMPLATE_NAME_IMPL(decode_template,Params)<boost::mpl::size_t<ID> BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SEQ_SIZE(Params), P) >::type


#define BOOST_TYPEOF_REGISTER_COMPACT_TEMPLATE_PARAM_PAIR(z,n,elem)\
   BOOST_TYPEOF_COMPACT_TYPE(BOOST_TYPEOF_MAKE_OBJ(elem)) BOOST_PP_CAT(P, n)

#endif //BOOST_TYPEOF_COMPLIANT_REGISTER_TEMPLATE_TEMPLATE_HPP_INCLUDED