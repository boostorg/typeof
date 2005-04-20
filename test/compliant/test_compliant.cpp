// Copyright (C) 2005 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#include <boost/typeof/typeof.hpp>

// this test would not work for MSVC 7.0 and earlier, 
// since Spirit/Lambda are not supported

#if !(BOOST_WORKAROUND(BOOST_MSVC, <= 1300))

#ifdef _MSC_VER
#   pragma warning(disable:4512)
#endif

#include "spirit/register.hpp"
#include "lambda/register.hpp"
#include <libs/typeof/test/stl/register.hpp>
#include <cassert>
#include <iostream>

#define BOOST_TYPEOF_TEXT "compiling Lambda example..."
#include <boost/typeof/message.hpp>

void test_lambda()
{
    using namespace boost::lambda;

    BOOST_AUTO(fun, _1 > 15 && _2 < 20);
    int n = 19;
    
    if (!fun(n, n))
        throw 0;

    std::cout << typeid(fun).name() << std::endl;
}

#define BOOST_TYPEOF_TEXT "compiling Spirit example..."
#include <boost/typeof/message.hpp>

void test_spirit1()
{
    using namespace boost::spirit;
    using namespace boost::lambda;
    using namespace std;

    vector<double> v;

    BOOST_AUTO(parser,
        (real_p[push_back_a(v)] >> *(',' >> real_p[push_back_a(v)]))
        );

    parse("3.14159, 2.71828", parser, space_p);

    for_each(v.begin(), v.end(), cout << _1 << ' ');
    cout << endl;
}

#define BOOST_TYPEOF_TEXT "compiling another Spirit example..."
#include <boost/typeof/message.hpp>

void test_spirit2()
{
    using namespace boost::spirit;

    BOOST_AUTO(
        skipper,
        (       space_p
            |   "//" >> *(anychar_p - '\n') >> '\n'
            |   "/*" >> *(anychar_p - "*/") >> "*/"
        )
    );

    bool success = parse(
        "/*this is a comment*/\n//this is a c++ comment\n\n",
        *skipper).full;

    if (!success)
        throw 0;
}

#define BOOST_TYPEOF_TEXT "negate test"
#include <boost/typeof/message.hpp>

#include <functional>
namespace negate_test
{
	template<class T> 
	std::negate<T> make_negate(const T&);

    template <class T>
    BOOST_TYPEOF_TPL(make_negate(T())(T()))
    operator-(T const& x)
    {
        return std::negate<T>()(x);
    }
}

#endif//!(BOOST_WORKAROUND(BOOST_MSVC, <= 1300))
