// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_INT_ENCODING_HPP_INCLUDED
#define BOOST_TYPEOF_INT_ENCODING_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost
{
    namespace type_of
    {
        template<class T, T n> 
        struct split
        {
            static const size_t u = (size_t)n; 
            static const size_t value1 = (u >> 16) + 1;
            static const size_t value2 = (u << 16 >> 16) + 1;
        };

        template<class T, size_t u1, size_t u2>
        struct join
        {
            static const T value = (T)(((u1 - 1) << 16) + (u2 - 1));
        };

        template<class V, class T, T n>
        struct encode_long_integral
        {
            typedef
                typename BOOST_TYPEOF_PUSH_BACK<
                typename BOOST_TYPEOF_PUSH_BACK<
                V
                , mpl::size_t<split<T, n>::value1> >::type
                , mpl::size_t<split<T, n>::value2> >::type
                type;
        };

        template<class T, class Iter> 
        struct decode_long_integral
        {
            static const T value = join<
                T,
                mpl::deref<Iter>::type::value,
                mpl::deref<typename mpl::next<Iter>::type>::type::value
            >::value;

            typedef typename mpl::next<typename mpl::next<Iter>::type>::type iter;
        };

        template<class V, class T, T n>
        struct encode_short_integral
        {
            typedef
                typename BOOST_TYPEOF_PUSH_BACK<
                V
                , mpl::size_t<(size_t)n + 1> >::type
                type;
        };

        template<class T, class Iter> 
        struct decode_short_integral
        {
            static const T value = (T)(mpl::deref<Iter>::type::value - 1);
            typedef typename mpl::next<Iter>::type iter;
        };

        template<class V, class T, T n>
        struct encode_integral : mpl::if_c<
            (sizeof(T) < 4),
            encode_short_integral<V, T, n>,
            encode_long_integral<V, T, n>
            >::type
        {};

        template<class T, class Iter> 
        struct decode_integral : mpl::if_c<
            (sizeof(T) < 4),
            decode_short_integral<T, Iter>,
            decode_long_integral<T, Iter>
            >::type
        {};
    }
}//namespace 

#endif//BOOST_TYPEOF_INT_ENCODING_HPP_INCLUDED
