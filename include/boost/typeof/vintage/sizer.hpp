// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_SIZER_HPP_HOLT_2004_0819
#define BOOST_TYPEOF_SIZER_HPP_HOLT_2004_0819

#ifdef BOOST_MAX_RECURSION
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#endif

namespace boost{namespace type_of {

/*
The reason for a sizer class to extract the size of a type from, 
is that using the size of a function returning an array limits the size of the array to 0x7FFFFFF
(At least on VC 6.5) This is ok when representing type identifiers, 
but not when representing integral types such as mpl::int_<0xFFFFFFFF>.
Also, VC 7.0 does not do well with function references returning an array ( char (&f())[N];)
sizer can be used to represent any number from 1 to 0xFFFFFFFF.
*/
template<unsigned S>
struct sizer {
    enum {value1=S/2};
    enum {value2=S-S/2};
    char a[value1];
    char b[value2];
};

template<>
struct sizer<1> {
    char type;
};

template<>
struct sizer<0xFFFFFFFF> {
    char a[0x7FFFFFFF];
    char b[0x7FFFFFFF];
    char c;
};

template<>
struct sizer<0> {
  //Unable to represent a type with zero size.
};

template<int N> struct encode_counter : encode_counter<N - 1> {};
template<> struct encode_counter<0> {};

#ifdef BOOST_MAX_RECURSION
#define BOOST_TYPEOF_SPECIALIZE_ENCODE_COUNTER(z,n,text)\
template<> struct encode_counter<BOOST_MAX_RECURSION*BOOST_PP_INC(n)> {};

BOOST_PP_REPEAT(20,BOOST_TYPEOF_SPECIALIZE_ENCODE_COUNTER,_)
#undef BOOST_TYPEOF_SPECIALIZE_ENCODE_COUNTER


template<typename T,int N=BOOST_MAX_RECURSION>
struct counter_start
{
   template<bool> 
   struct increase_limit {
      BOOST_STATIC_CONSTANT(unsigned,value=(counter_start<T,N+BOOST_MAX_RECURSION>::value));
   };
   template<>
   struct increase_limit<false>
   {
      BOOST_STATIC_CONSTANT(unsigned,value=N-1);
   };
   BOOST_STATIC_CONSTANT(unsigned,current=N-1);
   BOOST_STATIC_CONSTANT(unsigned,next=N+BOOST_MAX_RECURSION-1);

   BOOST_STATIC_CONSTANT(bool,exceed_current=(sizeof(encode_index((encode_counter<current>*)NULL))==current));
   BOOST_STATIC_CONSTANT(bool,start_next=(sizeof(encode_index((encode_counter<next>*)NULL))>1));
   BOOST_STATIC_CONSTANT(unsigned,value=(increase_limit<exceed_current&&start_next>::value));
   typedef encode_counter<value> type;
};

#define BOOST_TYPEOF_INDEX(T) (sizeof(boost::type_of::encode_index((boost::type_of::counter_start<T>::type*)0)))
#else

#define BOOST_TYPEOF_INDEX(T) (sizeof(boost::type_of::encode_index((boost::type_of::encode_counter<BOOST_MAX_TYPEOF_COUNTER+BOOST_MIN_TYPEOF_COUNTER>*)0)))

#endif

#define BOOST_TYPEOF_VALUE(A,B) (sizeof(boost::type_of::encode_value(A(),B())))


sizer<1> encode_value(...);
//Need a large starting value, due to MSVC's ETI errors.
sizer<BOOST_MIN_TYPEOF_COUNTER> encode_index(...);
/*
#define BOOST_TYPEOF_VALUE(N) (sizeof(boost::type_of::encode_value((boost::type_of::encode_counter<N>*)0)))
#define BOOST_TYPEOF_INDEX() (sizeof(*boost::type_of::encode_index((boost::type_of::encode_counter<BOOST_MAX_TYPEOF_COUNTER+BOOST_MIN_TYPEOF_COUNTER>*)0)))
*/

}}//namespace boost::type_of

#endif //BOOST_TYPEOF_SIZER_HPP_HOLT_2004_0819

