// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_IS_POINTER_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_IS_POINTER_HPP_INCLUDED

#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_array.hpp>

namespace boost { namespace type_of {
    template<typename T>
    boost::detail::yes_type is_pointer_tester(T*);
    boost::detail::no_type is_pointer_tester(...);

    template <bool>
    struct is_pointer_select
        : ::boost::type_traits::false_result
    {
    };

    template <>
    struct is_pointer_select<false>
    {
        template <typename T> struct result_
        {
            static T& make_t();
            BOOST_STATIC_CONSTANT(bool, value =
                        (1 == sizeof(is_pointer_tester(make_t())))
                    );
        };
    };

    template <typename T>
    struct is_pointer_impl
        : is_pointer_select<
              ::boost::type_traits::ice_or<
                  ::boost::is_reference<T>::value
                , ::boost::is_array<T>::value
                >::value
            >::template result_<T>
    {
    };

    template<typename T>
    struct is_pointer : is_pointer_impl<T>
    {};

    template<>
    struct is_pointer<void> : ::boost::mpl::false_
    {};
}}//namespace boost::type_of

#endif //BOOST_TYPEOF_VINTAGE_IS_POINTER_HPP_INCLUDED
