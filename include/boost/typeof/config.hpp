// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_CONFIG_HPP_INCLUDED
#define BOOST_TYPEOF_CONFIG_HPP_INCLUDED

#if !defined(BOOST_TYPEOF_COMPLIANT) && !defined(BOOST_TYPEOF_VINTAGE) && !defined(BOOST_TYPEOF_NATIVE) 

#	if defined __GNUC__
#		define BOOST_TYPEOF_NATIVE

#	elif defined  __MWERKS__
#		define BOOST_TYPEOF_NATIVE

#	elif defined BOOST_TYPEOF_NO_PARTIAL_TEMPLATE_SPECIALIZATION
#		define BOOST_TYPEOF_VINTAGE

#	else
#		define BOOST_TYPEOF_COMPLIANT

#	endif

#endif

#endif//BOOST_TYPEOF_CONFIG_HPP_INCLUDED
