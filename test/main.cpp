// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#pragma message("including typeof.hpp...")
#include <boost/typeof/typeof.hpp>
#pragma message("done")

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/static_assert.hpp>
#include <boost/noncopyable.hpp>

#include <cassert>
#include <iostream>
#include <vector>

#include "stl/register.hpp"
#include "mpl/register.hpp"

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

using namespace std;

template<class T> 
struct typeof_test
{
    static T foo();
    enum {value = boost::is_same<
        BOOST_TYPEOF_TPL(typeof_test::foo()),  //fully qualify foo() to avoid problems with g++
        typename boost::remove_reference<typename boost::remove_const<T>::type>::type
    >::value};
};

#pragma message("started")

struct x
{};

BOOST_TYPEOF_REGISTER_TYPE(x);

template<class T, char c, unsigned short us, 
    int i, unsigned long ul, bool b1, bool b2, unsigned u> struct with_integrals
{};

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

#pragma message("integral...")
BOOST_STATIC_ASSERT((typeof_test<with_integrals<int, 5, 4, 3, 2, true, false, 5> >::value));
BOOST_STATIC_ASSERT((typeof_test<with_integrals<int, 1, 1, 0, ULONG_MAX, false, true, 0> >::value));

#pragma message("namespace-level functions...")
BOOST_STATIC_ASSERT(typeof_test<double(*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<double(*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<void(*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<void(*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);

#pragma message("member functions...")
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<void(x::*)()>::value);
BOOST_STATIC_ASSERT(typeof_test<void(x::*)(int, double, short, char*, bool, char, float, long, unsigned short)>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()const>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()volatile>::value);
BOOST_STATIC_ASSERT(typeof_test<double(x::*)()volatile const>::value);
//BOOST_STATIC_ASSERT(typeof_test<static double(x::*)()volatile const>::value);

#pragma message("data members...")
BOOST_STATIC_ASSERT(typeof_test<double x::*>::value);

#pragma message("modifiers...")
BOOST_STATIC_ASSERT((typeof_test<boost::mpl::vector3<const int* const, const int[20], const int&>*>::value));
BOOST_STATIC_ASSERT((typeof_test<boost::mpl::vector2<const int* const, const int&>&>::value));
BOOST_STATIC_ASSERT((typeof_test<boost::mpl::vector1<int[5]> >::value));
BOOST_STATIC_ASSERT((typeof_test<boost::mpl::vector1<const int[5]> >::value));

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

BOOST_TYPEOF_REGISTER_TYPE(boost::noncopyable);

struct noncopiable_test
{
    const boost::noncopyable& foo();
    void bar()
    {
        BOOST_AUTO(const& v, foo());
    }
};

#pragma message("ODR...")
void odr_test()
{
    void odr_test1();
    void odr_test2();
    odr_test1();
    odr_test2();
}

#pragma message("main()...")
main()
{
    odr_test();
}

#pragma message("done!")
