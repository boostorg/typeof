// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

template<>
struct encode_impl<ARRAY_ID+n>
{
    template<typename V,typename T,typename Types>
    struct encoder {
        BOOST_STATIC_CONSTANT(unsigned,size=(sizeof(*((T*)NULL))/sizeof((*((T*)NULL))[0])));
        typedef typename mpl::next<typename mpl::next<V>::type>::type next_type;
        typedef void(*function_ptr)(
            sizer<ARRAY_ID+n>,
            next_type,
            T,
            Types
        );
        BOOST_STATIC_CONSTANT(unsigned,value=sizeof(encode(function_ptr(NULL))));

        friend sizer<ARRAY_ID+n> encode_value(const sizer<V::index>&,const sizer<V::pos>&);
        friend sizer<size> encode_value(const sizer<V::index>&,const sizer<(V::pos)+1>&);
    };
};
template<typename V,typename T,typename Types>
typename encode_modifier<V,T,Types>::encoded_type encode(void(*)(sizer<ARRAY_ID+n>,V,T BOOST_TYPEOF_qualifier[],Types));

template<>
struct decode_impl<ARRAY_ID+n>
{
    template<typename Iter>
    struct decoder {
        BOOST_STATIC_CONSTANT(unsigned,size=Iter::value);
        typedef typename Iter::next iter1;
        typedef typename decode_impl<iter1::value>::decoder<iter1::next> decode1;
        typedef typename decode1::type BOOST_TYPEOF_qualifier type[size];
        typedef typename decode1::iter iter;
    };
};
