// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_INT_ENCODING_HPP_INCLUDED
#define BOOST_TYPEOF_VINTATE_INT_ENCODING_HPP_INCLUDED

#include <boost/config.hpp>

namespace boost {namespace type_of {

template<unsigned N>
struct encode_integral_wrapper {};

template<unsigned N>
struct encode_integral {
    template<typename V,typename Types>
    struct encoder {
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(typename encode_modifier<typename mpl::next<V>::type,typename Types::type,typename Types::next>::encoded_type));
        
        friend sizer<N^0x80000000> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
    };
};
//Special implementation for 0x80000000 and 0x7FFFFFFF in order to allow representation of all numbers
template<>
struct encode_integral<0x80000000> 
{
    template<typename V,typename Types>
    struct encoder {
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(typename encode_modifier<typename mpl::next<typename mpl::next<V>::type>::type,typename Types::type,typename Types::next>::encoded_type));
        
        friend sizer<0xFFFFFFFF> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
        friend sizer<0x80000000> encode_value(const sizer<V::index>&,const sizer<(V::pos)+1>&);
    };
};

template<>
struct encode_integral<0x7FFFFFFF> 
{
    template<typename V,typename Types>
    struct encoder {
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(typename encode_modifier<typename mpl::next<typename mpl::next<V>::type>::type,typename Types::type,typename Types::next>::encoded_type));
        
        friend sizer<0xFFFFFFFF> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
        friend sizer<0x7FFFFFFF> encode_value(const sizer<V::index>&,const sizer<(V::pos)+1>&);
    };
};

template<unsigned N,typename V,typename Types>
typename encode_integral<N>::encoder<V,Types> encode(encode_integral_wrapper<N> const&(*)(V,Types));

template<unsigned N>
struct decode_integral_base {
    template<typename Iter>
    struct decoder {
        BOOST_STATIC_CONSTANT(int,value=N^0x80000000);
        typedef Iter iter;
    };
#if BOOST_WORKAROUND(BOOST_MSVC,<=1300)
    template<>
    struct decoder<int> {
        BOOST_STATIC_CONSTANT(unsigned,value=1);
        typedef int iter;
    };
#endif
};

template<>
struct decode_integral_base<0xFFFFFFFF> {
    template<typename Iter>
    struct decoder {
        BOOST_STATIC_CONSTANT(int,value=Iter::value);
        typedef typename Iter::next iter;
    };
#if BOOST_WORKAROUND(BOOST_MSVC,<=1300)
    template<>
    struct decoder<int> {
        BOOST_STATIC_CONSTANT(unsigned,value=1);
        typedef int iter;
    };
#endif
};

template<typename Iter>
struct decode_integral : decode_integral_base<TYPEOF_GET_VALUE(Iter)>::decoder<TYPEOF_GET_NEXT(Iter)>
{
};

template<unsigned N>
struct encode_unsigned_integral_wrapper {};

template<unsigned N>
struct encode_unsigned_integral {
    template<typename V,typename Types>
    struct encoder {
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(typename encode_modifier<typename mpl::next<V>::type,typename Types::type,typename Types::next>::encoded_type));
        
        friend sizer<N+1> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
    };
};

template<>
struct encode_unsigned_integral<0xFFFFFFFF> {
    template<typename V,typename Types>
    struct encoder {
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(typename encode_modifier<typename mpl::next<typename mpl::next<V>::type>::type,typename Types::type,typename Types::next>::encoded_type));
        
        friend sizer<0xFFFFFFFF> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
        friend sizer<0xFFFFFFFF> encode_value(const sizer<V::index>&,const sizer<(V::pos)+1>&);
    };
};

template<>
struct encode_unsigned_integral<0xFFFFFFFE> {
    template<typename V,typename Types>
    struct encoder {
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(typename encode_modifier<typename mpl::next<typename mpl::next<V>::type>::type,typename Types::type,typename Types::next>::encoded_type));
        
        friend sizer<0xFFFFFFFF> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
        friend sizer<0xFFFFFFFE> encode_value(const sizer<V::index>&,const sizer<(V::pos)+1>&);
    };
};

template<unsigned N,typename V,typename Types>
typename encode_unsigned_integral<N>::encoder<V,Types> encode(encode_unsigned_integral_wrapper<N> const&(*)(V,Types));

template<unsigned N>
struct decode_unsigned_integral_base
{
    template<typename Iter>
    struct decoder {
        BOOST_STATIC_CONSTANT(unsigned,value=N-1);
        typedef Iter iter;
    };
#if BOOST_WORKAROUND(BOOST_MSVC,<=1300)
    template<>
    struct decoder<int> {
        BOOST_STATIC_CONSTANT(unsigned,value=1);
        typedef int iter;
    };
#endif
};

template<>
struct decode_unsigned_integral_base<0xFFFFFFFF> {
    template<typename Iter>
    struct decoder {
        BOOST_STATIC_CONSTANT(unsigned,value=Iter::value);
        typedef typename Iter::next iter;
    };
#if BOOST_WORKAROUND(BOOST_MSVC,<=1300)
    template<>
    struct decoder<int> {
        BOOST_STATIC_CONSTANT(unsigned,value=1);
        typedef int iter;
    };
#endif
};

template<typename Iter>
struct decode_unsigned_integral : decode_unsigned_integral_base<TYPEOF_GET_VALUE(Iter)>::decoder<TYPEOF_GET_NEXT(Iter)>
{
};

}}//namespace boost::type_of

#endif //BOOST_TYPEOF_INTEGRAL_WRAPPER_HPP_HOLT_2004_0818
