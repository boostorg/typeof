// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#pragma message("including typeof.hpp...")
#include <boost/typeof/typeof.hpp>
#pragma message("done")

#include <boost/detail/workaround.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <boost/noncopyable.hpp>

#include <cassert>
#include <iostream>

#include "mpl/register.hpp"

#include <boost/typeof/std/string.hpp>
#include <boost/typeof/std/deque.hpp>
#include <boost/typeof/std/list.hpp>
#include <boost/typeof/std/queue.hpp>
#include <boost/typeof/std/stack.hpp>
#include <boost/typeof/std/vector.hpp>
#include <boost/typeof/std/map.hpp>
#include <boost/typeof/std/set.hpp>
#include <boost/typeof/std/bitset.hpp>
#include <boost/typeof/std/functional.hpp>
#include <boost/typeof/std/valarray.hpp>
#include <boost/typeof/std/locale.hpp>
#include <boost/typeof/std/iostream.hpp>
#include <boost/typeof/std/streambuf.hpp>
#include <boost/typeof/std/istream.hpp>
#include <boost/typeof/std/ostream.hpp>
#include <boost/typeof/std/sstream.hpp>
#include <boost/typeof/std/fstream.hpp>
#include <boost/typeof/std/iterator.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

using namespace std;
using namespace boost;

template<class T> 
mpl::vector1<T> typeof_test_helper(mpl::vector1<T>*);

template<class T> 
struct typeof_test
{
    enum {value = boost::is_same<
        BOOST_TYPEOF_TPL(typeof_test_helper(reinterpret_cast<mpl::vector1<T>*>(0))),
        mpl::vector1<T>
        >::value
    };
};

#pragma message("modifiers...")

BOOST_STATIC_ASSERT(typeof_test<int*>::value);
BOOST_STATIC_ASSERT(typeof_test<int&>::value);
BOOST_STATIC_ASSERT(typeof_test<int[20]>::value);
BOOST_STATIC_ASSERT(typeof_test<const int>::value);
BOOST_STATIC_ASSERT(typeof_test<volatile int>::value);
BOOST_STATIC_ASSERT(typeof_test<volatile const int>::value);
BOOST_STATIC_ASSERT(typeof_test<volatile int[20]>::value);
BOOST_STATIC_ASSERT(typeof_test<volatile const int[20]>::value);

BOOST_STATIC_ASSERT((typeof_test<boost::mpl::vector3<const int* const, const int[20], const int&>*>::value));
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
BOOST_STATIC_ASSERT((typeof_test<boost::mpl::vector2<const int* const, const int&>&>::value));
#endif
BOOST_STATIC_ASSERT((typeof_test<boost::mpl::vector1<int[5]> >::value));
BOOST_STATIC_ASSERT((typeof_test<boost::mpl::vector1<const int[5]> >::value));

#pragma message("started")

struct x
{};

BOOST_TYPEOF_REGISTER_TYPE(x)

template<class T, char c, unsigned short us, 
    int i, unsigned long ul, bool b1, bool b2, signed char sc, unsigned u> struct with_integrals
{};

BOOST_TYPEOF_REGISTER_TEMPLATE_X(with_integrals, 
    (class)
    (char)
    (unsigned short)
    (int)
    (unsigned long)
    (bool)
    (bool)
    (signed char)
    (unsigned)
    )

#pragma message("integral...")
BOOST_STATIC_ASSERT((typeof_test<with_integrals<int, 5, 4, -3, 2, true, false, -1, 5> >::value));
BOOST_STATIC_ASSERT((typeof_test<with_integrals<int, 1, 1, 0, ULONG_MAX, false, true, -1, 0> >::value));

#pragma message("namespace-level function pointers...")
BOOST_STATIC_ASSERT(typeof_test<double(*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<double(*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<void(*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<void(*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);


#ifdef BOOST_TYPEOF_COMPLIANT
#  pragma message("function references...")
   BOOST_STATIC_ASSERT(typeof_test<void(&)()>::value);
   BOOST_STATIC_ASSERT(typeof_test<int(&)(int, short)>::value);
#endif//BOOST_TYPEOF_COMPLIANT

#ifdef BOOST_TYPEOF_COMPLIANT 
#   pragma message("function values...")
    BOOST_STATIC_ASSERT(typeof_test<void()>::value);
    BOOST_STATIC_ASSERT(typeof_test<double(bool)>::value);
#endif//BOOST_TYPEOF_COMPLIANT

#pragma message("member functions...")
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<void(x::*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<void(x::*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()const>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()volatile>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()volatile const>::value);

#pragma message("data members...")
BOOST_STATIC_ASSERT(typeof_test<double x::*>::value);

#pragma message("Lvalue test...")
void lvalue_typeof_test()
{
    int n;
    const int cn = 0;
    int& rn = n;
    const int& rcn = cn;
    int f();
    //const int cf();
    int& rf();
    const int& rcf();

    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(n), int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(cn), const int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rn), int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rcn), const int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(f()), int>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rf()), int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rcf()), const int&>::value));
    //BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(cf()), const int&>::value));
    //BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(21), int>::value));
    //BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(int(21)), int>::value));
}

#pragma message("Noncopyable...")

BOOST_TYPEOF_REGISTER_TYPE(boost::noncopyable)

const boost::noncopyable& noncopiable_test_helper();

struct noncopiable_test
{
    void bar()
    {
        BOOST_AUTO(const& v, noncopiable_test_helper());
        v; // to avoid warning
    }
};

#pragma message("STL containers...")

BOOST_STATIC_ASSERT(typeof_test<string>::value);
BOOST_STATIC_ASSERT(typeof_test<deque<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<list<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<queue<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<stack<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<vector<int> >::value);
BOOST_STATIC_ASSERT((typeof_test<map<int, int> >::value));
BOOST_STATIC_ASSERT((typeof_test<multimap<int, int> >::value));
BOOST_STATIC_ASSERT(typeof_test<set<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<multiset<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<bitset<10> >::value);

#pragma message("function objects...")

BOOST_STATIC_ASSERT((typeof_test<unary_function<int, int> >::value));
BOOST_STATIC_ASSERT((typeof_test<binary_function<int, int, int> >::value));
BOOST_STATIC_ASSERT(typeof_test<plus<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<minus<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<multiplies<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<divides<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<modulus<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<negate<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<equal_to<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<not_equal_to<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<greater<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<less<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<greater_equal<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<less_equal<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<logical_and<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<logical_or<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<logical_not<int> >::value);
BOOST_STATIC_ASSERT(typeof_test<unary_negate<negate<int> > >::value);
BOOST_STATIC_ASSERT(typeof_test<binary_negate<less<int> > >::value);
BOOST_STATIC_ASSERT(typeof_test<binder1st<less<int> > >::value);
BOOST_STATIC_ASSERT(typeof_test<binder2nd<less<int> > >::value);

#pragma message("valarray...")

BOOST_STATIC_ASSERT(typeof_test<valarray<int> >::value);

#pragma message("compiling integral param wrapper...")

namespace test_integral
{
    // Enum template parameter
    enum E{ONE, TWO, THREE};

    template<E e> struct foo
    {
        BOOST_STATIC_CONSTANT(E,value=e);
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

#pragma message("ODR...")
void odr_test()
{
    void odr_test1();
    void odr_test2();
    odr_test1();
    odr_test2();
}

#pragma message("main()...")
int main()
{
    odr_test();
}

#pragma message("done!")
