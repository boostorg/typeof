// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_TYPE_ENCODING_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_TYPE_ENCODING_HPP_INCLUDED

#include <boost/typeof/config.hpp>

#define BOOST_TYPEOF_ENCODE_TYPE(simple_type)\
    template<>\
    struct encode_impl<BOOST_TYPEOF_UNIQUE_ID()>\
    {\
        template<typename V,typename Types>\
        struct encoder {\
            BOOST_STATIC_CONSTANT(unsigned,value=\
                sizeof(\
                    typename encode_modifier<\
                        typename mpl::next<V>::type,\
                        typename Types::type,\
                        typename Types::next\
                    >::encoded_type\
                )\
            );\
            friend sizer<BOOST_TYPEOF_UNIQUE_ID()> encode_value(const sizer<V::index>&,const sizer<V::pos>&);\
        };\
    };\
    template<typename V,typename Types>\
    typename encode_impl<BOOST_TYPEOF_UNIQUE_ID()>::encoder<V,Types> encode(simple_type const& (*)(V,Types));

#define BOOST_TYPEOF_DECODE_TYPE(simple_type)\
    template<>\
    struct decode_impl<BOOST_TYPEOF_UNIQUE_ID()>\
    {\
        template<typename Iter>\
        struct decoder {\
            typedef simple_type type;\
            typedef Iter iter;\
        };\
    };\

#define BOOST_TYPEOF_REGISTER_TYPE(simple_type)\
namespace boost { namespace type_of{\
BOOST_TYPEOF_ENCODE_TYPE(simple_type)\
BOOST_TYPEOF_DECODE_TYPE(simple_type)\
}}//namespace boost::type_of

#endif //BOOST_TYPEOF_VINTAGE_TYPE_ENCODING_HPP_INCLUDED