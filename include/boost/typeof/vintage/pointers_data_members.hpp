// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_VINTAGE_POINTERS_DATA_MEMBERS_HPP_INCLUDED
#define BOOST_TYPEOF_VINTAGE_POINTERS_DATA_MEMBERS_HPP_INCLUDED

#include <boost/typeof/config.hpp>
#include <boost/typeof/vintage/concatenate.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

namespace boost { namespace type_of{ 
    enum {PTR_DATA_MEM_ID = BOOST_TYPEOF_UNIQUE_ID()};

    template<>
    struct encode_impl<PTR_DATA_MEM_ID>
    {
        template<typename V,typename R,typename T,typename Types>
        struct encoder {
            typedef Types types_2; 
            typedef type_list< T, types_2 > types_1; 
            typedef type_list< R, types_1 > types_0; 
            BOOST_STATIC_CONSTANT(unsigned,value=
                sizeof( 
                    typename encode_modifier<
                        typename mpl::next<V>::type, 
                        typename types_0::type,
                        types_1
                    >::encoded_type
                )
            );
            friend sizer<PTR_DATA_MEM_ID> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
        };
    };
    template<typename R,typename T,typename V,typename Types>
    typename encode_impl<PTR_DATA_MEM_ID>::template encoder<V,R,T,Types>
    encode(R (T::* const&(*function)(V,Types)));

    template<> struct decode_impl<PTR_DATA_MEM_ID> { 
        template<typename Iter> 
        struct decoder { 
            typedef Iter iter0;
            BOOST_TYPEOF_DECODE_PARAMS(2)

            template<typename R,typename T> struct workaround{
                typedef R (T::*type);
            };
            template<> struct workaround<int,int>{
                typedef int type;
            };

            typedef workaround<A0,A1>::type type;
            typedef iter2 iter; 
        }; 
    };
}} //namespace boost::type_of

#endif //BOOST_TYPEOF_REGISTER_MEMBER_POINTER_HPP_HOLT_2004_1015