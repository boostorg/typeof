// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_TYPE_LIST_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_TYPE_LIST_HPP_INCLUDED

namespace boost{ namespace type_of{
    struct empty_type_list {
        typedef empty_type_list type;
        typedef empty_type_list next;
    };
    template<typename T,typename Next=empty_type_list>
    struct type_list {
        typedef T type;
        typedef Next next;
    };

    template<typename V,typename Types>
    int 
    encode(empty_type_list const& (*)(V,Types));

}}//namespace boost::type_of

#endif //BOOST_TYPEOF_VINTAGE_TYPE_LIST_HPP_INCLUDED

