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
    //assert(fun(n, n));

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

    //assert(success);
}


