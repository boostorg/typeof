// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef LAMBDA_REGISTER_HPP_INCLUDED
#define LAMBDA_REGISTER_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/tuple/tuple.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

// will pick up shortest
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tuples::tuple, 10)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::tuples::tuple, 2)

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::lambda::lambda_functor, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::lambda::lambda_functor_base, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::lambda::relational_action, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::lambda::logical_action, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::lambda::other_action, 1)
BOOST_TYPEOF_REGISTER_TYPE(boost::lambda::equal_action)
BOOST_TYPEOF_REGISTER_TYPE(boost::lambda::greater_action)
BOOST_TYPEOF_REGISTER_TYPE(boost::lambda::less_action)
BOOST_TYPEOF_REGISTER_TYPE(boost::lambda::and_action)
BOOST_TYPEOF_REGISTER_TYPE(boost::lambda::subscript_action)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::lambda::placeholder, (int))

#endif//LAMBDA_REGISTER_HPP_INCLUDED
