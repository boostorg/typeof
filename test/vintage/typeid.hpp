// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef TYPEID_HPP_INCLUDED
#define TYPEID_HPP_INCLUDED

#include <string>

template<bool IsReference,bool IsConst>
struct typeid_base {
    template<typename T>
    struct inner {
        static std::string name()
        {
            return typeid(T).name();
        }
    };
};

template<>
struct typeid_base<true,false> {
    template<typename T>
    struct inner {
        static std::string name()
        {
            return std::string(typeid(T).name())+"&";
        }
    };
};

template<>
struct typeid_base<false,true> {
    template<typename T>
    struct inner {
        static std::string name()
        {
            return std::string(typeid(T).name())+" const";
        }
    };
};

template<>
struct typeid_base<true,true> {
    template<typename T>
    struct inner {
        static std::string name()
        {
            return std::string(typeid(T).name())+" const&";
        }
    };
};

template<class T> struct type_id
:   typeid_base<boost::is_reference<T>::value,boost::is_const<T>::value>::inner<T>
{    
};

#endif//TYPEID_HPP_INCLUDED

