// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_TYPEOF_HPP_INCLUDED
#define BOOST_TYPEOF_TYPEOF_HPP_INCLUDED

// implementation

#include <boost/typeof/config.hpp>

// BOOST_TYPEOF, BOOST_TYPEOF_TPL

#if defined(BOOST_TYPEOF_COMPLIANT)
#	include <boost/typeof/compliant/typeof_impl.hpp>

#elif defined(BOOST_TYPEOF_VINTAGE)
// include something to define BOOST_TYPEOF, BOOST_TYPEOF_TPL

#else//BOOST_TYPEOF_NATIVE

#	if !defined BOOST_TYPEOF
#		define BOOST_TYPEOF __typeof__
#	endif
#	define BOOST_TYPEOF_TPL BOOST_TYPEOF

#endif

// auto

#define BOOST_AUTO(Var, Expr) BOOST_TYPEOF(Expr) Var(Expr)
#define BOOST_AUTO_TPL(Var, Expr) BOOST_TYPEOF_TPL(Expr) Var(Expr)

// lvalue typeof

#if defined(BOOST_TYPEOF_VINTAGE)
// include lvalue_typeof definition
#else
#	include <boost/typeof/compliant/lvalue_typeof.hpp>
#endif

// type/template encoding

#if defined(BOOST_TYPEOF_COMPLIANT)
#	include <boost/typeof/compliant/type_encoding.hpp>
#	include <boost/typeof/compliant/template_encoding.hpp>
#elif defined(BOOST_TYPEOF_VINTAGE)
// include type encoding definitions
#else//BOOST_TYPEOF_NATIVE
#	define BOOST_TYPEOF_REGISTER_TYPE(x)
#	define BOOST_TYPEOF_REGISTER_TEMPLATE_X(x, params)
#endif

#define BOOST_TYPEOF_REGISTER_TEMPLATE_TYPE_PARAM_(z, n, data) (typename)

#define BOOST_TYPEOF_REGISTER_TEMPLATE(Name, n)\
    BOOST_TYPEOF_REGISTER_TEMPLATE_X(Name,\
        BOOST_PP_REPEAT(n, BOOST_TYPEOF_REGISTER_TEMPLATE_TYPE_PARAM_, ~)\
    )

#define BOOST_TYPEOF_UNIQUE_ID()\
    BOOST_TYPEOF_REGISTRATION_GROUP * 0x10000 + __LINE__

#define BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()\
    <boost/typeof/increment_registration_group.hpp>

// register stuff

#include <boost/typeof/register_fundamental.hpp>

#if defined(BOOST_TYPEOF_COMPLIANT)

#	include <boost/typeof/compliant/modifiers.hpp>
#	include <boost/typeof/compliant/pointers_data_members.hpp>
#	define BOOST_PP_FILENAME_1 <boost/typeof/compliant/register_functions_iterate.hpp>
#	include <boost/typeof/register_functions.hpp>

#elif defined(BOOST_TYPEOF_VINTAGE)
//	include stuff here
#else //BOOST_TYPEOF_NATIVE
#endif

#endif//BOOST_TYPEOF_TYPEOF_HPP_INCLUDED