// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef TYPEID_HPP_INCLUDED
#define TYPEID_HPP_INCLUDED

#include <string>

template<class T> struct type_id
{
    static std::string name()
    {
        return typeid(T).name();
    }
};
template<class T> struct type_id<T&>
{
    static std::string name()
    {
        return type_id<T>::name() + "&";
    }
};
template<class T> struct type_id<const T>
{
    static std::string name()
    {
        return std::string("const ") + type_id<T>::name();
    }
};

#endif//TYPEID_HPP_INCLUDED

