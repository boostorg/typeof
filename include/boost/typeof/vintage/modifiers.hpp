// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_VINTAGE_TYPEOF_MODIFIERS_HPP_INCLUDED
#define BOOST_VINTAGE_TYPEOF_MODIFIERS_HPP_INCLUDED

#include <boost/typeof/vintage/type_list.hpp>
#include <boost/typeof/vintage/encode_decode.hpp>
#include <boost/mpl/next.hpp>

namespace boost { namespace type_of {

sizer<0xffff> encode(...);
template<unsigned N>
struct validate_type {
    template<typename T>
    struct use_BOOST_TYPEOF_REGISTER_TYPE {
        typedef int type;
    };
};

template<>
struct validate_type<0xffff> {
    template<typename T>
    struct use_BOOST_TYPEOF_REGISTER_TYPE {
    };
};

template<>
struct encode_impl<NO_MODIFIERS>
{
    template<typename V,typename T,typename Types>
    struct encoder {
        typedef T const& (*function_ptr)(V,Types);
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(encode(function_ptr(NULL))));
        //If T is a template type, use BOOST_TYPEOF_REGISTER_TEMPLATE.
        typedef validate_type<value>::use_BOOST_TYPEOF_REGISTER_TYPE<T>::type type_validation;
    };
};

template<>
struct encode_impl<FUNCTION_OR_MEMBER_ID>
{
    template<typename V,typename T,typename Types>
    struct encoder {
        typedef T& (*function_ptr)(V,Types);
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(encode(function_ptr(NULL))));
    };
};

template<>
struct encode_impl<VOID_ID>
{
    template<typename V,typename T,typename Types>
    struct encoder {
        BOOST_STATIC_CONSTANT(unsigned,value=
            sizeof(
                typename encode_modifier<
                    typename mpl::next<V>::type,
                    typename Types::type,
                    typename Types::next
                >::encoded_type
            )
        );
        friend sizer<VOID_ID> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
    };
};

template<>
struct decode_impl<VOID_ID>
{
    template<typename Iter>
    struct decoder {
        typedef void type;
        typedef Iter iter;
    };
};

#define BOOST_TYPEOF_qualifier
#define n 0
#include <boost/typeof/vintage/modifier_pointer.hpp>
#include <boost/typeof/vintage/modifier_reference.hpp>
#include <boost/typeof/vintage/modifier_array.hpp>
#undef n
#undef BOOST_TYPEOF_qualifier

#define BOOST_TYPEOF_qualifier const
#define n 1
#include <boost/typeof/vintage/modifier_qualifier.hpp>
#include <boost/typeof/vintage/modifier_pointer.hpp>
#include <boost/typeof/vintage/modifier_reference.hpp>
#include <boost/typeof/vintage/modifier_array.hpp>
#undef n
#undef BOOST_TYPEOF_qualifier

#define BOOST_TYPEOF_qualifier volatile
#define n 2
#include <boost/typeof/vintage/modifier_qualifier.hpp>
#include <boost/typeof/vintage/modifier_pointer.hpp>
#include <boost/typeof/vintage/modifier_reference.hpp>
#include <boost/typeof/vintage/modifier_array.hpp>
#undef n
#undef BOOST_TYPEOF_qualifier

#define BOOST_TYPEOF_qualifier const volatile
#define n 3
#include <boost/typeof/vintage/modifier_qualifier.hpp>
#include <boost/typeof/vintage/modifier_pointer.hpp>
#include <boost/typeof/vintage/modifier_reference.hpp>
#include <boost/typeof/vintage/modifier_array.hpp>
#undef n
#undef BOOST_TYPEOF_qualifier

}} //namespace boost::type_of

#endif //BOOST_VINTAGE_TYPEOF_MODIFIERS_HPP_INCLUDED