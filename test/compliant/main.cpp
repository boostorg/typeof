// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#pragma message("including typeof.hpp...")
#include <boost/typeof/typeof.hpp>
#pragma message("done")

#include <boost/noncopyable.hpp>
#include <boost/type_traits/is_same.hpp>

#pragma message("registering")
#include "stl/register.hpp"
#include "mpl/register.hpp"
#include "spirit/register.hpp"
#include "lambda/register.hpp"
#pragma message("done")

#include <cassert>
#include <iostream>
#include <vector>

#include <boost/lambda/lambda.hpp>
#include <boost/spirit.hpp>
#include <boost/mpl/vector.hpp>
#include "typeid.hpp"

using namespace std;

#pragma message("started")

double f_0()
{
    cout << "functions with no params" << endl;
    return 0;
}
double f_9(int, double, short, char*, bool, char, float, long, unsigned short)
{
    cout << "functions with 9 params" << endl;
    return 0;
}
void vf_0()
{
    cout << "void functions with 0 params" << endl;
}
void vf_9(int, double, short, char*, bool, char, float, long, unsigned short)
{
    cout << "void functions with 9 params" << endl;
}

struct x
{
    int f_0() volatile
    {
        cout << "member functions with no params" << endl;
        return 0;
    }
    int f_9(int, double, char, int, double, char, int, double, char)
    {
        cout << "member functions with 9 params" << endl;
        return 0;
    }
    void vf_0()
    {
        cout << "void member functions with no params" << endl;
    }
    void vf_9(int, double, char, int, double, char, int, double, char)
    {
        cout << "void member functions with 9 params" << endl;
    }
    int cf_0() const volatile
    {
        cout << "const member functions with no params" << endl;
        return 0;
    }
    int cf_9(int, double, char, int, double, char, int, double, char) const
    {
        cout << "const member functions with 9 params" << endl;
        return 0;
    }
    void cvf_0() const
    {
        cout << "const void member functions with no params" << endl;
    }
    void cvf_9(int, double, char, int, double, char, int, double, char) const
    {
        cout << "const void member functions with 9 params" << endl;
    }
    static void sf_0()
    {
        cout << "static member function" << endl;
    }
    std::vector<int> m_v;
};

struct noncop : boost::noncopyable
{};
const noncop& foo_nc()
{
    static noncop nc;
    return nc;
}

template<class T, char c, unsigned short us, 
    int i, unsigned long ul, bool b1, bool b2, unsigned u> struct with_integrals
{};

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(x)
BOOST_TYPEOF_REGISTER_TEMPLATE_X(with_integrals, 
    (class)
    (char)
    (unsigned short)
    (int)
    (unsigned long)
    (bool)
    (bool)
    (unsigned)
    );

BOOST_TYPEOF_REGISTER_TYPE(noncop)

main()
{
#pragma message("integral...")
    {
        with_integrals<int, 5, 4, 3, 2, true, false, 5> expr;
        BOOST_AUTO(v, expr);
        v;
        with_integrals<int, 1, 1, 0, ULONG_MAX, false, true, 0> expr1;
        BOOST_AUTO(v1, expr1);
        v1;
    }
#pragma message("Noncopyable...")
    {
        //BOOST_AUTO(v, foo_nc());
        BOOST_AUTO(const& v, foo_nc());
    }
#pragma message("Lvalue preserving...")
    {
        int n;
        const int cn = 0;
        int& rn = n;
        const int& rcn = cn;
        int f();
        //const int cf();
        int& rf();
        const int& rcf();

        cout << type_id<BOOST_LVALUE_TYPEOF(n)>::name() << endl;
        cout << type_id<BOOST_LVALUE_TYPEOF(cn)>::name() << endl;
        cout << type_id<BOOST_LVALUE_TYPEOF(rn)>::name() << endl;
        cout << type_id<BOOST_LVALUE_TYPEOF(rcn)>::name() << endl;
        cout << type_id<BOOST_LVALUE_TYPEOF(f())>::name() << endl;
        //cout << type_id<BOOST_LVALUE_TYPEOF(cf())>::name() << endl;
        cout << type_id<BOOST_LVALUE_TYPEOF(rf())>::name() << endl;
        cout << type_id<BOOST_LVALUE_TYPEOF(rcf())>::name() << endl;
        cout << type_id<BOOST_LVALUE_TYPEOF(21)>::name() << endl;
        cout << type_id<BOOST_LVALUE_TYPEOF(int(21))>::name() << endl;

        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(n), int&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(cn), const int&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rn), int&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rcn), const int&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(f()), int>::value));
        //BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(cf()), const int&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rf()), int&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rcf()), const int&>::value));
        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(21), int>::value));
        BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(int(21)), int>::value));
    }
#pragma message("compiling Lambda example...")
    {
        using namespace boost::lambda;

        BOOST_AUTO(fun, _1 > 15 && _2 < 20);
        int n = 19;
        assert(fun(n, n));

        std::cout << typeid(fun).name() << std::endl;
    }
#pragma message("compiling Spirit example...")
    {
        // spirit example

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
    {
        // more spirit...
        
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

        assert(success);
    }
#pragma message("compiling Modifiers example...")
    {
        //modifiers

        using namespace std;
        using namespace boost;

        // top-level pointers are preserved...

        mpl::vector3<const int* const, const int[20], const int&>* foo();
        cout << typeid(BOOST_TYPEOF(foo())).name() << endl;

        // ... but top-level refs are not :(

        mpl::vector2<const int* const, const int&>& bar();
        cout << typeid(BOOST_TYPEOF(bar())).name() << endl;
        
        mpl::vector1<int[5]> vi;
        cout << "int[5]" << endl;
        cout << typeid(BOOST_TYPEOF(vi)).name() << endl;

        mpl::vector1<const int[5]> vci;
        cout << "const int[5]" << endl;
        cout << typeid(BOOST_TYPEOF(vci)).name() << endl;
    }
#pragma message("compiling functions example...")
    {
        BOOST_AUTO(p0, &f_0);
        (*p0)();
        
        BOOST_AUTO(p9, &f_9);
        (*p9)(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
#pragma message("compiling void functions example...")
    {
        BOOST_AUTO(p0, &vf_0);
        (*p0)();
        
        BOOST_AUTO(p9, &vf_9);
        (*p9)(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
#pragma message("compiling member functions example...")
    {
        x xx;

        BOOST_AUTO(p0, &x::f_0);
        (xx.*p0)();
        
        BOOST_AUTO(p9, &x::f_9);
        (xx.*p9)(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
#pragma message("compiling void member functions example...")
    {
        x xx;

        BOOST_AUTO(p0, &x::vf_0);
        (xx.*p0)();
        
        BOOST_AUTO(p9, &x::vf_9);
        (xx.*p9)(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
#pragma message("compiling const member functions example...")
    {
        x xx;

        BOOST_AUTO(p0, &x::cf_0);
        (xx.*p0)();
        
        BOOST_AUTO(p9, &x::cf_9);
        (xx.*p9)(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
#pragma message("compiling const void member functions example...")
    {
        x xx;

        BOOST_AUTO(p0, &x::cvf_0);
        (xx.*p0)();
        
        BOOST_AUTO(p9, &x::cvf_9);
        (xx.*p9)(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
#pragma message("compiling static member functions example...")
    {
        BOOST_AUTO(p0, &x::sf_0);
        (*p0)();
    }
#pragma message("pointers to data members...")
    {
        BOOST_AUTO(p, &x::m_v);
        x xx;
        (xx.*p).push_back(1);
    }
#pragma message("ODR")

    void odr_test1();
    void odr_test2();
    odr_test1();
    odr_test2();

#pragma message("done!")
}

