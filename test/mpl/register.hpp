// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef MPL_REGISTER_HPP_INCLUDED
#define MPL_REGISTER_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/mpl/vector.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(boost::mpl::vector0<>)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::mpl::vector1, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::mpl::vector2, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::mpl::vector3, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::mpl::vector4, 4)

#endif//MPL_REGISTER_HPP_INCLUDED
