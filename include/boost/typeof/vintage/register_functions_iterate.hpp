// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#define n BOOST_PP_ITERATION()

template<>
struct encode_impl<FUN_REF_ID + n>
{
    template<typename V,typename R BOOST_PP_ENUM_TRAILING_PARAMS(n,typename A),typename Types>
    struct encoder {
        typedef Types BOOST_PP_CAT(types_,n);
        BOOST_PP_REPEAT(n,BOOST_TYPEOF_PUSH_FRONT,n)
        BOOST_STATIC_CONSTANT(int,instantiate =
            sizeof(
                encode_modifier<
                    mpl::next<V>::type,
                    R,
                    types_0
                >::encoded_type
            )
        );
        friend sizer<FUN_REF_ID + n> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
    };
};

template<typename V,typename R BOOST_PP_ENUM_TRAILING_PARAMS(n,typename A),typename Types>
typename encode_impl<FUN_REF_ID + n>::template encoder<V,R BOOST_PP_ENUM_TRAILING_PARAMS(n,A),Types>
encode(R (& (*function)(V,Types))(BOOST_PP_ENUM_PARAMS(n,A)) );

template<>
struct decode_impl<FUN_REF_ID + n>
{
    template<typename Iter>
    struct decoder {
        typedef Iter iterR;
        typedef decode_impl<TYPEOF_GET_VALUE(iterR)>::decoder<TYPEOF_GET_NEXT(iterR)> decodeR;
        typedef typename decodeR::type R;
        typedef typename decodeR::iter iter0;
        BOOST_TYPEOF_DECODE_PARAMS(n);
        typedef R (&type)(BOOST_PP_ENUM_PARAMS(n,A));
        typedef BOOST_PP_CAT(iter,n) iter;
    };
};

template<>
struct encode_impl<FUN_ID + n>
{
    template<typename V,typename R BOOST_PP_ENUM_TRAILING_PARAMS(n,typename A),typename Types>
    struct encoder {
        typedef Types BOOST_PP_CAT(types_,n);
        BOOST_PP_REPEAT(n,BOOST_TYPEOF_PUSH_FRONT,n)
        BOOST_STATIC_CONSTANT(int,instantiate =
            sizeof(
                encode_modifier<
                    mpl::next<V>::type,
                    R,
                    types_0
                >::encoded_type
            )
        );
        friend sizer<FUN_ID + n> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
    };
};

template<typename V,typename R BOOST_PP_ENUM_TRAILING_PARAMS(n,typename A),typename Types>
typename encode_impl<FUN_ID + n>::template encoder<V,R BOOST_PP_ENUM_TRAILING_PARAMS(n,A),Types>
encode(R (* const& (*function)(V,Types))(BOOST_PP_ENUM_PARAMS(n,A)) );

template<>
struct decode_impl<FUN_ID + n>
{
    template<typename Iter>
    struct decoder {
        typedef Iter iterR;
        typedef decode_impl<TYPEOF_GET_VALUE(iterR)>::decoder<TYPEOF_GET_NEXT(iterR)> decodeR;
        typedef typename decodeR::type R;
        typedef typename decodeR::iter iter0;
        BOOST_TYPEOF_DECODE_PARAMS(n);
        typedef R (*type)(BOOST_PP_ENUM_PARAMS(n,A));
        typedef BOOST_PP_CAT(iter,n) iter;
    };
};

#define BOOST_TYPEOF_qualifier 
#define BOOST_TYPEOF_id MEM_FUN_ID

#include <boost/typeof/vintage/register_mem_functions.hpp>

#define BOOST_TYPEOF_qualifier const
#define BOOST_TYPEOF_id CONST_MEM_FUN_ID

#include <boost/typeof/vintage/register_mem_functions.hpp>

#define BOOST_TYPEOF_qualifier volatile 
#define BOOST_TYPEOF_id VOLATILE_MEM_FUN_ID

#include <boost/typeof/vintage/register_mem_functions.hpp>

#define BOOST_TYPEOF_qualifier volatile const
#define BOOST_TYPEOF_id VOLATILE_CONST_MEM_FUN_ID

#include <boost/typeof/vintage/register_mem_functions.hpp>

#undef n