// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_COMPLIANT_MODIFIERS_HPP_INCLUDED
#define BOOST_TYPEOF_COMPLIANT_MODIFIERS_HPP_INCLUDED

#include <boost/typeof/compliant/encode_decode.hpp>
#include <boost/typeof/compliant/concatenate.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

namespace boost
{
    namespace type_of
    {
        namespace
        {
            enum
            {
                CONST_ID = BOOST_TYPEOF_UNIQUE_ID(), 
                PTR_ID, 
                REF_ID,
                ARRAY_ID,
                CONST_ARRAY_ID
            };

            template<class V, class T> struct encode_type_impl<V, const T> 
            {
                typedef 
                    typename encode_type<
                    typename BOOST_TYPEOF_PUSH_BACK<
                    V
                    , mpl::size_t<CONST_ID> >::type
                    , T>::type 
                    type;
            };
            template<class Iter> struct decode_type_impl<mpl::size_t<CONST_ID>, Iter>
            {
                typedef decode_type<Iter> d1;
                typedef const typename d1::type type;
                typedef typename d1::iter iter;
            };
            template<class V, class T> struct encode_type_impl<V, T*> 
            {
                typedef 
                    typename encode_type<
                    typename BOOST_TYPEOF_PUSH_BACK<
                    V
                    , mpl::size_t<PTR_ID> >::type
                    , T>::type 
                    type;
            };
            template<class Iter> struct decode_type_impl<mpl::size_t<PTR_ID>, Iter>
            {
                typedef decode_type<Iter> d1;
                typedef typename d1::type* type;
                typedef typename d1::iter iter;
            };
            template<class V, class T> struct encode_type_impl<V, T&> 
            {
                typedef 
                    typename encode_type<
                    typename BOOST_TYPEOF_PUSH_BACK<
                    V
                    , mpl::size_t<REF_ID> >::type
                    , T>::type 
                    type;
            };
            template<class Iter> struct decode_type_impl<mpl::size_t<REF_ID>, Iter>
            {
                typedef decode_type<Iter> d1;
                typedef typename d1::type& type;
                typedef typename d1::iter iter;
            };
            template<class V, class T, int N> struct encode_type_impl<V, T[N]>
            {
                typedef 
                    typename encode_type<
                    typename BOOST_TYPEOF_PUSH_BACK<
                    typename BOOST_TYPEOF_PUSH_BACK<
                    V
                    , mpl::size_t<ARRAY_ID> >::type
                    , mpl::size_t<N> >::type
                    , T>::type 
                type;
            };
            template<class Iter> struct decode_type_impl<mpl::size_t<ARRAY_ID>, Iter>
            {
                enum{n = mpl::deref<Iter>::type::value}; 
                typedef decode_type<typename mpl::next<Iter>::type> d;
                typedef typename d::type type[n];
                typedef typename d::iter iter;
            };
            template<class V, class T, int N> struct encode_type_impl<V, const T[N]>
            {
                typedef 
                    typename encode_type<
                    typename BOOST_TYPEOF_PUSH_BACK<
                    typename BOOST_TYPEOF_PUSH_BACK<
                    V
                    , mpl::size_t<CONST_ARRAY_ID> >::type
                    , mpl::size_t<N> >::type
                    , T>::type 
                type;
            };
            template<class Iter> struct decode_type_impl<mpl::size_t<CONST_ARRAY_ID>, Iter>
            {
                enum{n = mpl::deref<Iter>::type::value}; 
                typedef decode_type<typename mpl::next<Iter>::type> d;
                typedef typename d::type const type[n];
                typedef typename d::iter iter;
            };
        }
    }
}

#endif//BOOST_TYPEOF_COMPLIANT_MODIFIERS_HPP_INCLUDED
