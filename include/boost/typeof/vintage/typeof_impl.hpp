// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_TYPEOF_IMPL_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_TYPEOF_IMPL_HPP_INCLUDED

#include <boost/typeof/vintage/encode_decode.hpp>
#include <boost/typeof/vintage/sizer.hpp>
namespace boost
{
	namespace type_of
	{
        template<unsigned Index,unsigned Position=1>
        struct iterator {
            BOOST_STATIC_CONSTANT(unsigned,index=Index);
            BOOST_STATIC_CONSTANT(unsigned,pos=Position);
            typedef iterator<Index,pos+1> next;
        };

        template<typename T>
        struct encode_type
        {
           BOOST_STATIC_CONSTANT(unsigned,value=BOOST_TYPEOF_INDEX(T));
           BOOST_STATIC_CONSTANT(unsigned,encode_dummy=sizeof(BOOST_DEDUCED_TYPENAME encode_modifier<iterator<value>,T,empty_type_list>::encoded_type));

           BOOST_STATIC_CONSTANT(unsigned,next=value+1);
           friend sizer<next> encode_index(encode_counter<next>*);

           sizer<value> resize;
        };

        template<typename T>
        encode_type<T> encode_start(T const&);

        template<typename Iter>
        struct decode {
            typedef typename decode_impl<Iter::value>::decoder<Iter::next>::type type;
        };
        template<>
        struct decode<int> {
            typedef int type;
        };
        template<unsigned Index,unsigned Position=1>
        struct value_iterator {
            BOOST_STATIC_CONSTANT(unsigned,pos=Position);
            BOOST_STATIC_CONSTANT(unsigned,value=BOOST_TYPEOF_VALUE(sizer<Index>,sizer<pos>));
            typedef value_iterator<Index,pos+1> next;
        };
    }
}

#define BOOST_TYPEOF(expr) \
    boost::type_of::decode<boost::type_of::value_iterator<sizeof(boost::type_of::encode_start(expr))> >::type

#define BOOST_TYPEOF_TPL(expr) typename BOOST_TYPEOF(expr)


#endif//BOOST_TYPEOF_VINTAGE_TYPEOF_IMPL_HPP_INCLUDED


