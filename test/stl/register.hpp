// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef STL_REGISTER_HPP_INCLUDED
#define STL_REGISTER_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>

#include <vector>
#include <set>
#include <list>
#include <map>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(std::vector, (class)(class))
BOOST_TYPEOF_REGISTER_TEMPLATE(std::list, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(std::set, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(std::allocator, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(std::less, 1)

#endif//STL_REGISTER_HPP_INCLUDED
