#pragma warning(disable:4512)

#include <boost/typeof/typeof.hpp>

#include "spirit/register.hpp"
#include "lambda/register.hpp"
#include <libs/typeof/test/stl/register.hpp>
#include <cassert>
#include <iostream>

#pragma message("compiling Lambda example...")
void test_lambda()
{
    using namespace boost::lambda;

    BOOST_AUTO(fun, _1 > 15 && _2 < 20);
    int n = 19;
    
    if (!fun(n, n))
        throw 0;

    std::cout << typeid(fun).name() << std::endl;
}

#pragma message("compiling Spirit example...")
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

#pragma message("compiling another Spirit example...")
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

#pragma message("compiling integral param wrapper...")

namespace test_integral
{
    // Enum template parameter
    enum E{ONE, TWO, THREE};

    template<E e> struct foo
    {
        static const E value = e;
    };

    // dependent template parameter
    template<class T, T n> struct bar
    {};

    // multi-word template parameter
    template<unsigned long int n> struct blah
    {};
}

BOOST_TYPEOF_REGISTER_TEMPLATE_X(test_integral::foo, 
                                 (BOOST_TYPEOF_INTEGRAL(test_integral::E))
                                );

BOOST_TYPEOF_REGISTER_TEMPLATE_X(test_integral::blah, 
                                (BOOST_TYPEOF_INTEGRAL(unsigned long int))
                                );

BOOST_TYPEOF_REGISTER_TEMPLATE_X(test_integral::bar, 
                                (class)
                                (BOOST_TYPEOF_INTEGRAL(P0))
                                );

namespace test_integral
{
    void test()
    {
        foo<TWO> x;
        bar<int, 5> xx;
        blah<5> xxx;

        BOOST_AUTO(y, x);
        BOOST_AUTO(yy, xx);
        BOOST_AUTO(yyy, xxx);

        y;
        yy;
        yyy;
    }
}
