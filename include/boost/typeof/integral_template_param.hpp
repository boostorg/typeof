// Copyright (C) 2005 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED
#define BOOST_TYPEOF_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED

#define BOOST_TYPEOF_unsigned (unsigned)
#define BOOST_TYPEOF_signed (signed)

#define char_BOOST_TYPEOF (char)
#define short_BOOST_TYPEOF (short)
#define int_BOOST_TYPEOF (int)
#define long_BOOST_TYPEOF (long)

#define BOOST_TYPEOF_char_BOOST_TYPEOF (char)
#define BOOST_TYPEOF_short_BOOST_TYPEOF (short)
#define BOOST_TYPEOF_int_BOOST_TYPEOF (int)
#define BOOST_TYPEOF_long_BOOST_TYPEOF (long)
#define BOOST_TYPEOF_bool_BOOST_TYPEOF (bool)
#define BOOST_TYPEOF_unsigned_BOOST_TYPEOF (unsigned)
#define BOOST_TYPEOF_size_t_BOOST_TYPEOF (size_t)

#define BOOST_TYPEOF_MAKE_OBJ_char          BOOST_TYPEOF_INTEGRAL_PARAM(char,char)
#define BOOST_TYPEOF_MAKE_OBJ_short         BOOST_TYPEOF_INTEGRAL_PARAM(short,short)
#define BOOST_TYPEOF_MAKE_OBJ_int           BOOST_TYPEOF_INTEGRAL_PARAM(int,int)
#define BOOST_TYPEOF_MAKE_OBJ_long          BOOST_TYPEOF_INTEGRAL_PARAM(long,long)
#define BOOST_TYPEOF_MAKE_OBJ_bool          BOOST_TYPEOF_INTEGRAL_PARAM(bool,bool)
#define BOOST_TYPEOF_MAKE_OBJ_unsigned      BOOST_TYPEOF_INTEGRAL_PARAM(unsigned,uint)
#define BOOST_TYPEOF_MAKE_OBJ_size_t        BOOST_TYPEOF_INTEGRAL_PARAM(size_t,size_t)
#define BOOST_TYPEOF_MAKE_OBJ_unsignedchar  BOOST_TYPEOF_INTEGRAL_PARAM(unsigned char,uchar)
#define BOOST_TYPEOF_MAKE_OBJ_unsignedshort BOOST_TYPEOF_INTEGRAL_PARAM(unsigned short,ushort)
#define BOOST_TYPEOF_MAKE_OBJ_unsignedint   BOOST_TYPEOF_INTEGRAL_PARAM(unsigned int,uint)
#define BOOST_TYPEOF_MAKE_OBJ_unsignedlong  BOOST_TYPEOF_INTEGRAL_PARAM(unsigned long,ulong)
#define BOOST_TYPEOF_MAKE_OBJ_signedchar    BOOST_TYPEOF_INTEGRAL_PARAM(signed char,schar)
#define BOOST_TYPEOF_MAKE_OBJ_signedshort   BOOST_TYPEOF_INTEGRAL_PARAM(signed short,short)
#define BOOST_TYPEOF_MAKE_OBJ_signedint     BOOST_TYPEOF_INTEGRAL_PARAM(signed int,int)
#define BOOST_TYPEOF_MAKE_OBJ_signedlong    BOOST_TYPEOF_INTEGRAL_PARAM(signed long,long)
#define BOOST_TYPEOF_MAKE_OBJ_integral(x)   BOOST_TYPEOF_EXPLICIT_INTEGRAL_PARAM(x)

#define BOOST_TYPEOF_INTEGRAL(X) integral(X) BOOST_TYPEOF_EAT
#define BOOST_TYPEOF_EAT_BOOST_TYPEOF
#define BOOST_TYPEOF_integral(X) (integral(X))

#define BOOST_TYPEOF_INTEGRAL_PARAM(Type,Name)\
    (INTEGRAL_PARAM)\
    (Type)\
    (Name)

#define BOOST_TYPEOF_EXPLICIT_INTEGRAL_PARAM(Type)\
    (EXPLICIT_INTEGRAL_PARAM)\
    (Type)\
    (BOOST_PP_CAT(_,Type))

#define BOOST_TYPEOF_DECODE_EXPLICIT_INTEGRAL_PARAM BOOST_TYPEOF_DECODE_INTEGRAL_PARAM
#define BOOST_TYPEOF_ENCODE_EXPLICIT_INTEGRAL_PARAM BOOST_TYPEOF_ENCODE_INTEGRAL_PARAM
#define BOOST_TYPEOF_EXPAND_INTEGRAL_PARAM(Param) BOOST_TYPEOF_PARAM_GETTYPE(Param)
#define BOOST_TYPEOF_EXPAND_EXPLICIT_INTEGRAL_PARAM(Param) BOOST_TYPEOF_PARAM_GETTYPE(Param)

#endif//BOOST_TYPEOF_INTEGRAL_TEMPLATE_PARAM_HPP_INCLUDED
