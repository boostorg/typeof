// Copyright (C) 2018 Tobias Loew
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)


#include <boost/typeof/typeof.hpp>

namespace detail {
    template<class T> inline T& deref(T& r) {
        return  r;
    }
    template<class T>
    struct wrapper {
        typedef T type;
    };

    template<class T> wrapper<T> wrap(T&);
};


void test_typeof_in_lambda() {
    // Visual Studio 2015 (BOOST_MSVC == 1900) had an internal compiler error with Boost 1.65 and 1.66 when using BOOST_SCOPE_EXIT inside a lambda
    // the error was due to a change of include in boost/typeof/typeof.hpp  (<boost/typeof/decltype.hpp> instead of <boost/typeof/native.hpp>)
    // This test is an more or less minimal extract from the BOOST_SCOPE_EXIT macro expansions
    
    // worked also with VS 2015 in version 1.65/1.66
    int n;
    typedef BOOST_TYPEOF(::detail::wrap(::detail::deref(n))) n_type_wrapped;
    typedef  n_type_wrapped::type n_type;

    int test;

    auto check_property = [&n,&test]() {
        // internal compiler error with VS 2015 in version 1.65/1.66
        // minimal extract from
        //BOOST_SCOPE_EXIT(test) {
        //    test = 42;
        //}BOOST_SCOPE_EXIT_END

        // this compiles always (as long as the one before outside the lambda has the same name)
        typedef BOOST_TYPEOF(::detail::wrap(::detail::deref(n))) n_type_wrapped;
        typedef  n_type_wrapped::type n_type;

        // this fails with internal compiler error with VS 2015 in version 1.65/1.66
        typedef BOOST_TYPEOF(::detail::wrap(::detail::deref(test))) test_type_wrapped;
        typedef  test_type_wrapped::type test_type;

    };

}

int main() {
    test_typeof_in_lambda();

    return 0;
}
