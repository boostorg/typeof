// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_TYPE_TO_MACRO_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_TYPE_TO_MACRO_HPP_INCLUDED

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/seq.hpp>

/*
These macros are used to dechifer template arguments into sensible macros.
There are three predefined macro builders:
BOOST_TYPEOF_typename - for class and typename arguments
BOOST_TYPEOF_integral - for signed integral values, int,short,char,bool, etc.
BOOST_TYPEOF_unsigned_integral - for unsigned integral values, unsigned, unsigned long etc.

All the fundamental integral types (except long long) have been pre-registered.
In order to implement new template argument types (enums), 
you need to define a macro containing the name of the enum:

enum MyEnum {red=0,green=1,blue=2};
#define BOOST_TYPEOF__MyEnum__ BOOST_TYPEOF_integral

//MyEnum is now treated as an integral value in template expressions.

template<MyEnum value>
struct enum_class {};

//Is registered using
BOOST_TYPEOF_DEFINE_TEMPLATE(enum_class,1,(MyEnum))
*/

#define BOOST_TYPEOF_typename(dummy,append,arg) BOOST_PP_CAT(BOOST_TYPEOF_typename_,append)arg
#define BOOST_TYPEOF_integral(dummy,append,arg) BOOST_PP_CAT(BOOST_TYPEOF_integral_,append)arg
#define BOOST_TYPEOF_unsigned_integral(dummy,append,arg) BOOST_PP_CAT(BOOST_TYPEOF_unsigned_integral_,append)arg

#define BOOST_TYPEOF__typename__    BOOST_TYPEOF_typename BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__class__       BOOST_TYPEOF_typename BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__bool__        BOOST_TYPEOF_integral BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__char__        BOOST_TYPEOF_integral BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__short__       BOOST_TYPEOF_integral BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__int__         BOOST_TYPEOF_integral BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__long__        BOOST_TYPEOF_integral BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__unsigned__    BOOST_TYPEOF_unsigned_integral BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__signed__      BOOST_TYPEOF_integral BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__size_t__      BOOST_TYPEOF_unsigned_integral BOOST_PP_LPAREN() dummy
#define BOOST_TYPEOF__unsigned BOOST_TYPEOF_unsigned_integral BOOST_PP_LPAREN()
#define BOOST_TYPEOF__signed BOOST_TYPEOF_integral BOOST_PP_LPAREN()


#define BOOST_TYPEOF_WRAP2(expr) expr
#define BOOST_TYPEOF_WRAP1(expr) BOOST_TYPEOF_WRAP2 expr

#define BOOST_TYPEOF_ENCODE_ARGUMENT(z,n,text)\
  BOOST_TYPEOF_WRAP1((BOOST_PP_CAT(BOOST_TYPEOF__,BOOST_PP_CAT(text,__)),encode,(BOOST_PP_CAT(A,n)) BOOST_PP_RPAREN()))

#define BOOST_TYPEOF_ENCODE_SEQ_ELEMENT(z,n,seq)\
  BOOST_TYPEOF_ENCODE_ARGUMENT(z,n,BOOST_PP_SEQ_ELEM(n, seq))

#define BOOST_TYPEOF_DECODE_ARGUMENT(z,n,text)\
  BOOST_TYPEOF_WRAP1((BOOST_PP_CAT(BOOST_TYPEOF__,BOOST_PP_CAT(text,__)),decode,(n,text) BOOST_PP_RPAREN()))

#define BOOST_TYPEOF_DECODE_SEQ_ELEMENT(z,n,seq)\
  BOOST_TYPEOF_DECODE_ARGUMENT(z,n,BOOST_PP_SEQ_ELEM(n, seq))

#endif //BOOST_VINTAGE_TYPE_TO_MACRO_HPP_INCLUDED

