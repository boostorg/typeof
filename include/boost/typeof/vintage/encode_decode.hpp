// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_ENCODE_DECODE_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_ENCODE_DECODE_HPP_INCLUDED

#define BOOST_TYPEOF_UNIQUE_ID()\
    BOOST_TYPEOF_REGISTRATION_GROUP * 0x10000 + __LINE__

#define BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()\
    <boost/typeof/increment_registration_group.hpp>

#include <boost/typeof/vintage/modifier_category.hpp>

namespace boost
{
    namespace type_of
    {
        template<unsigned N>
        struct encode_impl {
            template<typename V,typename T,typename Types>
            struct encoder {    
            };
        };
        template<int>
        struct decode_impl{
            template<typename Iter>
            struct decoder {
                typedef int type;
                typedef int iter;
            };
        #if BOOST_WORKAROUND(BOOST_MSVC,<=1300)
            template<>
            struct decoder<int> {
                typedef int type;
                typedef int iter;
            };
        #endif
        };

        template<typename V,typename T,typename Types>
        struct encode_modifier {
            BOOST_STATIC_CONSTANT(unsigned,value=modifier_category<T>::value);
            typedef typename encode_impl<value>::template encoder<V,T,Types> encoded_type;
        };
    }
}

#endif//BOOST_TYPEOF_VINTAGE_ENCODE_DECODE_HPP_INCLUDED
