// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

//member functions
//This file must not be included directly.

template<>
struct encode_impl<BOOST_TYPEOF_id + n>
{
    template<typename V,typename R,typename T BOOST_PP_ENUM_TRAILING_PARAMS(n,typename A),typename Types>
    struct encoder {
        typedef Types BOOST_PP_CAT(types_,n);
        BOOST_PP_REPEAT(n,BOOST_TYPEOF_PUSH_FRONT,n)
        BOOST_STATIC_CONSTANT(int,instantiate =
            sizeof(
                encode_modifier<
                    mpl::next<V>::type,
                    R,
                    type_list<T,types_0>
                >::encoded_type
            )
        );
        friend sizer<BOOST_TYPEOF_id + n> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
    };
};

template<typename V,typename R,typename T BOOST_PP_ENUM_TRAILING_PARAMS(n,typename A),typename Types>
typename encode_impl<BOOST_TYPEOF_id + n>::template encoder<V,R,T BOOST_PP_ENUM_TRAILING_PARAMS(n,A),Types>
encode(R (T::* const&(*function)(V,Types))(BOOST_PP_ENUM_PARAMS(n,A)) BOOST_TYPEOF_qualifier);

template<>
struct decode_impl<BOOST_TYPEOF_id + n>
{
    template<typename Iter>
    struct decoder {
        typedef Iter iterR;
        typedef decode_impl<TYPEOF_GET_VALUE(iterR)>::decoder<TYPEOF_GET_NEXT(iterR)> decodeR;\
        typedef typename decodeR::type R;
        typedef typename decodeR::iter iterT;
        typedef decode_impl<TYPEOF_GET_VALUE(iterT)>::decoder<TYPEOF_GET_NEXT(iterT)> decodeT;\
        typedef typename decodeT::type T;
        typedef typename decodeT::iter iter0;
        BOOST_TYPEOF_DECODE_PARAMS(n)
        template<typename R_,typename T_ BOOST_PP_ENUM_TRAILING_PARAMS(n,typename A_)>
        struct workaround {
            typedef R_ (T_::*type)(BOOST_PP_ENUM_PARAMS(n,A_)) BOOST_TYPEOF_qualifier;
        };
        template<>
        struct workaround<int,int BOOST_PP_ENUM_TRAILING_PARAMS(n,int BOOST_PP_INTERCEPT)> {
            typedef int type;
        };
        typedef workaround<R,T BOOST_PP_ENUM_TRAILING_PARAMS(n,A)>::type type;
        typedef BOOST_PP_CAT(iter,n) iter;
    };
};

#undef BOOST_TYPEOF_id
#undef BOOST_TYPEOF_qualifier
