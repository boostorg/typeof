// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_MODIFIER_CATEGORY_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_MODIFIER_CATEGORY_HPP_INCLUDED

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/typeof/vintage/is_pointer.hpp>
#include <boost/config.hpp>

namespace boost { namespace type_of {
    enum {
        FUNCTION_OR_MEMBER_ID=BOOST_TYPEOF_UNIQUE_ID(),
        VOID_ID,
        NO_MODIFIERS,
        CONST_ID,
        VOLATILE_ID,
        CV_ID,
        POINTER_ID,
        CONST_POINTER_ID,
        VOLATILE_POINTER_ID,
        CV_POINTER_ID,
        REFERENCE_ID,
        CONST_REFERENCE_ID,
        VOLATILE_REFERENCE_ID,
        CV_REFERENCE_ID,
        ARRAY_ID,
        CONST_ARRAY_ID,
        VOLATILE_ARRAY_ID,
        CV_ARRAY_ID,
        MEMBER_POINTER_ID,
    };

template<typename U,int N>
struct cv_type {
    BOOST_STATIC_CONSTANT(unsigned,value=(N+is_const<U>::value+is_volatile<U>::value*2));
};

template<int Indirection>
struct indirection {
    template<typename T>
    struct inner {
        BOOST_STATIC_CONSTANT(unsigned,value=Indirection);
    };
};

template<>//pointer
struct indirection<POINTER_ID> {
    template<typename T>
    struct inner {
        template<typename U>
        static char (*test(U*))[cv_type<U,POINTER_ID>::value];
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(*test((T)NULL) ));
    };
};

template<>//reference
struct indirection<REFERENCE_ID> {
    template<typename T>
    struct inner {
        static T (*function)();

        template<typename U>
        static char (*test(U& (*)()))[cv_type<U,REFERENCE_ID>::value];

        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(*test(function)));
    };
};

template<>//array
struct indirection<ARRAY_ID> {
    template<typename T>
    struct inner {
        template<typename U>
        static char (*test(U []))[cv_type<U,ARRAY_ID>::value];

        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(*test(*((T*)NULL)) ));
    };
};

template<typename T>
struct modifier_category {    
    template<int cv>
    struct inner {
        BOOST_STATIC_CONSTANT(unsigned,value=NO_MODIFIERS+cv);
    };
    template<>
    struct inner<0> {
        BOOST_STATIC_CONSTANT(int,indir= (
            //boost::is_function<T>::value?FUNCTION_OR_MEMBER_ID:
            boost::is_array<T>::value?ARRAY_ID:
            boost::type_of::is_pointer<T>::value?POINTER_ID:
            boost::is_reference<T>::value?REFERENCE_ID:
            NO_MODIFIERS
        ));
        BOOST_STATIC_CONSTANT(unsigned,value=indirection<indir>::inner<T>::value);
    };

    BOOST_STATIC_CONSTANT(unsigned,cv=boost::is_array<T>::value?0:boost::is_const<T>::value+boost::is_volatile<T>::value*2);
    BOOST_STATIC_CONSTANT(unsigned,value=inner<cv>::value);
};

template<>
struct modifier_category<void>
{    
    BOOST_STATIC_CONSTANT(unsigned,value=VOID_ID);
};

}} //namespace boost::type_of

#endif //BOOST_TYPEOF_VINTAGE_MODIFIER_CATEGORY_HPP_INCLUDED

