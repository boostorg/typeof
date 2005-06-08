// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TYPEOF_TEXT "including typeof.hpp..."
#include <boost/typeof/message.hpp>

#include <boost/typeof/typeof.hpp>

#define BOOST_TYPEOF_TEXT "done"
#include <boost/typeof/message.hpp>

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

#ifdef BOOST_TYPEOF_COMPLIANT

#define BOOST_TYPEOF_TEXT "template template encoding..."
#include <boost/typeof/message.hpp>

namespace template_template {
    template<template<typename,unsigned int> class P0,int P1>
    struct tt_test {};

    template<typename A,unsigned int B> 
    struct C {};

    template<template<class, class> class T> 
    struct A;
}

BOOST_TYPEOF_REGISTER_TEMPLATE(template_template::A, (BOOST_TYPEOF_TEMPLATE(2)))

BOOST_TYPEOF_REGISTER_TEMPLATE(template_template::tt_test,
                               (BOOST_TYPEOF_TEMPLATE((typename)(unsigned int)))
                               (int)
                               )

BOOST_TYPEOF_REGISTER_TEMPLATE(template_template::C,
                               (typename)
                               (unsigned int)
                               )

BOOST_STATIC_ASSERT((typeof_test<template_template::tt_test<template_template::C,4> >::value));


#endif 

#define BOOST_TYPEOF_TEXT "modifiers..."
#include <boost/typeof/message.hpp>

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

struct x
{};

BOOST_TYPEOF_REGISTER_TYPE(x)

template<class T, char c, unsigned short us, 
    int i, unsigned long ul, bool b1, bool b2, signed char sc, unsigned u> struct with_integrals
{};

BOOST_TYPEOF_REGISTER_TEMPLATE(with_integrals, 
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

#define BOOST_TYPEOF_TEXT "integral..."
#include <boost/typeof/message.hpp>

BOOST_STATIC_ASSERT((typeof_test<with_integrals<int, 5, 4, -3, 2, true, false, -1, 5> >::value));
BOOST_STATIC_ASSERT((typeof_test<with_integrals<int, 1, 1, 0, ULONG_MAX, false, true, -1, 0> >::value));

#define BOOST_TYPEOF_TEXT "namespace-level function pointers..."
#include <boost/typeof/message.hpp>

BOOST_STATIC_ASSERT(typeof_test<double(*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<double(*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<void(*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<void(*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);


#ifdef BOOST_TYPEOF_COMPLIANT

#   define BOOST_TYPEOF_TEXT "function references..."
#   include <boost/typeof/message.hpp>

    BOOST_STATIC_ASSERT(typeof_test<void(&)()>::value);
    BOOST_STATIC_ASSERT(typeof_test<int(&)(int, short)>::value);
#endif//BOOST_TYPEOF_COMPLIANT

#ifdef BOOST_TYPEOF_COMPLIANT 

#   define BOOST_TYPEOF_TEXT "function values..."
#   include <boost/typeof/message.hpp>

    BOOST_STATIC_ASSERT(typeof_test<void()>::value);
    BOOST_STATIC_ASSERT(typeof_test<double(bool)>::value);
#endif//BOOST_TYPEOF_COMPLIANT

#define BOOST_TYPEOF_TEXT "member functions..."
#include <boost/typeof/message.hpp>

BOOST_STATIC_ASSERT(typeof_test<double(x::*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<void(x::*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<void(x::*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()const>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()volatile>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()volatile const>::value);

#define BOOST_TYPEOF_TEXT "data members..."
#include <boost/typeof/message.hpp>

BOOST_STATIC_ASSERT(typeof_test<double x::*>::value);

#define BOOST_TYPEOF_TEXT "Lvalue test..."
#include <boost/typeof/message.hpp>

void lvalue_typeof_test()
{
    int n;
    const int cn = 0;
    int& rn = n;
    const int& rcn = cn;
    int f();
    const int cf();
    int& rf();
    const int& rcf();

    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(n), int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(cn), const int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rn), int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rcn), const int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(f()), int>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rf()), int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(rcf()), const int&>::value));
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(cf()), const int&>::value));
    //BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(21), int>::value)); //msvc
    BOOST_STATIC_ASSERT((boost::is_same<BOOST_LVALUE_TYPEOF(int(21)), int>::value));
}
namespace ltype
{
    int& foo(double);
    char foo(int);

    template<class T> 
    struct result_type
    {
        typedef typename BOOST_LVALUE_TYPEOF(foo(T())) type;
    };

    BOOST_STATIC_ASSERT((boost::is_same<
        result_type<int>::type, 
        char
    >::value));

    BOOST_STATIC_ASSERT((boost::is_same<
        result_type<double>::type, 
        int&
    >::value));
};

#define BOOST_TYPEOF_TEXT "Noncopyable..."
#include <boost/typeof/message.hpp>

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

#define BOOST_TYPEOF_TEXT "STL containers..."
#include <boost/typeof/message.hpp>

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

#define BOOST_TYPEOF_TEXT "function objects..."
#include <boost/typeof/message.hpp>

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

#define BOOST_TYPEOF_TEXT "valarray..."
#include <boost/typeof/message.hpp>

BOOST_STATIC_ASSERT(typeof_test<valarray<int> >::value);

#define BOOST_TYPEOF_TEXT "compiling integral param wrapper..."
#include <boost/typeof/message.hpp>

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

BOOST_TYPEOF_REGISTER_TEMPLATE(test_integral::foo, 
                               (BOOST_TYPEOF_INTEGRAL(test_integral::E))
                               )

BOOST_TYPEOF_REGISTER_TEMPLATE(test_integral::blah, 
                               (BOOST_TYPEOF_INTEGRAL(unsigned long int))
                               )

BOOST_TYPEOF_REGISTER_TEMPLATE(test_integral::bar,
                               (class)
                               (BOOST_TYPEOF_INTEGRAL(P0))
                               )

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

        y = y;
        yy = yy;
        yyy = yyy;
    }
}

#define BOOST_TYPEOF_TEXT "ODR..."
#include <boost/typeof/message.hpp>

void odr_test()
{
    void odr_test1();
    void odr_test2();
    odr_test1();
    odr_test2();
}

#define BOOST_TYPEOF_TEXT "native/emulation consistency..."
#include <boost/typeof/message.hpp>

BOOST_STATIC_ASSERT((is_same<BOOST_TYPEOF(int()), int>::value));

#define BOOST_TYPEOF_TEXT "main()..."
#include <boost/typeof/message.hpp>

int main()
{
    odr_test();
	return 0;
}

#define BOOST_TYPEOF_TEXT "done!"
#include <boost/typeof/message.hpp>
