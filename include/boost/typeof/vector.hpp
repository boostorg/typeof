// Copyright (C) 2005 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

// Minimal replacement for mpl::vector<>.  
// Works a little faster with VC7.1 and a lot faster with GCC (compliant mode).
// Define BOOST_TYPEOF_USE_MPL_VECTOR to avoid it and use mpl::vector<> instead.

#ifndef BOOST_TYPEOF_VECTOR_HPP_INCLUDED
#define BOOST_TYPEOF_VECTOR_HPP_INCLUDED

#include <boost/mpl/at.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/int.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/comma_if.hpp>

#ifndef BOOST_TYPEOF_LIMIT_SIZE
#   define BOOST_TYPEOF_LIMIT_SIZE 50
#endif

// iterator

namespace boost{namespace type_of{
    template<class V, class Pos>
    struct v_iter
    {
        typedef typename boost::mpl::at<V, Pos>::type type;
        typedef v_iter<V, typename boost::mpl::next<Pos>::type> next;
    };
}}

// vector

#define BOOST_TYPEOF_typedef_item(z, n, _)\
    typedef P ## n item ## n;

#define BOOST_TYPEOF_define_vector(z, n, _)\
    template<BOOST_PP_ENUM_PARAMS(n, class P) BOOST_PP_COMMA_IF(n) class T = void>\
    struct vector ## n\
    {\
        typedef v_tag tag;\
        typedef v_iter<vector ## n, boost::mpl::int_<0> > begin;\
        typedef mpl::int_<n> size;\
        BOOST_PP_REPEAT(n, BOOST_TYPEOF_typedef_item, ~)\
    };

namespace boost{namespace type_of{
    class v_tag;
    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_TYPEOF_LIMIT_SIZE), BOOST_TYPEOF_define_vector, ~)
}}

#undef BOOST_TYPEOF_typedef_item
#undef BOOST_TYPEOF_define_vector

// at (specializing at rather than at_impl gives some performance gain)

#define BOOST_TYPEOF_spec_at(z, n, _)\
    template<class V>\
    struct at<V, int_<n> >\
    {\
        typedef typename V::item ## n type;\
    };

namespace boost{namespace mpl{
    BOOST_PP_REPEAT(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_spec_at, ~)
}}

/*
#define BOOST_TYPEOF_spec_at(z, n, _)\
    template<class V>\
    struct apply<V, int_<n> >\
    {\
        typedef typename V::item ## n type;\
    };

namespace boost{namespace mpl{
    template<>
    struct at_impl<boost::type_of::v_tag>
    {
        template<class V, class N>
        struct apply;
        BOOST_PP_REPEAT(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_spec_at, ~)
    };
}}
*/

#undef BOOST_TYPEOF_spec_at

// size

namespace boost{namespace mpl{
    template<>
    struct size_impl<boost::type_of::v_tag>
    {
        template<class V>
        struct apply
        {
            typedef typename V::size type;
        };
    };
}}

// push_back (specializing push_back rather than push_back_impl gives some performance gain)

#define BOOST_TYPEOF_spec_push_back(z, n, _)\
    template<BOOST_PP_ENUM_PARAMS(n, class P) BOOST_PP_COMMA_IF(n) class T>\
    struct push_back<BOOST_PP_CAT(boost::type_of::vector, n)<BOOST_PP_ENUM_PARAMS(n, P)>, T>\
    {\
        typedef BOOST_PP_CAT(boost::type_of::vector, BOOST_PP_INC(n))<\
            BOOST_PP_ENUM_PARAMS(n, P) BOOST_PP_COMMA_IF(n) T\
        > type;\
    };

namespace boost{namespace mpl{
    BOOST_PP_REPEAT(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_spec_push_back, ~)
}}

/*
#define BOOST_TYPEOF_spec_push_back(z, n, _)\
    template<BOOST_PP_ENUM_PARAMS(n, class P) BOOST_PP_COMMA_IF(n) class T>\
    struct apply<BOOST_PP_CAT(boost::type_of::vector, n)<BOOST_PP_ENUM_PARAMS(n, P)>, T>\
    {\
        typedef BOOST_PP_CAT(boost::type_of::vector, BOOST_PP_INC(n))<\
            BOOST_PP_ENUM_PARAMS(n, P) BOOST_PP_COMMA_IF(n) T\
        > type;\
    };

namespace boost{namespace mpl{
    template<>
    struct push_back_impl<boost::type_of::v_tag>
    {
        template<class V, class T>
        struct apply;
        BOOST_PP_REPEAT(BOOST_TYPEOF_LIMIT_SIZE, BOOST_TYPEOF_spec_push_back, ~)
    };
}}
*/

#undef BOOST_TYPEOF_spec_push_back

#endif//BOOST_TYPEOF_COMPLIANT_VECTOR_HPP_INCLUDED



