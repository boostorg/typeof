// Copyright (C) 2004 Arkadiy Vertleyb
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef ODR_HPP_INCLUDED
#define ODR_HPP_INCLUDED

#include <boost/typeof/typeof.hpp>

void odr_test1();
void odr_test2();

// trying to cause ODR violation in a class template

#if BOOST_WORKAROUND(BOOST_MSVC,==1200)

    // trying to cause ODR violation in a class template

    template<class T, class U>
    class sum_t
    {
    public:
    //    VC7 fails using template types in typeof expression.
        typedef BOOST_TYPEOF_TPL(T() + U()) result_type;

        sum_t(const T& t, const U& u);
        BOOST_TYPEOF_TPL(T() + U()) operator()();
    private:
        BOOST_TYPEOF_TPL(T() + U()) m_sum;
    };

    template<class T, class U>
    sum_t<T,U>::sum_t(const T& t, const U& u)
    :   m_sum(t + u)
    {}

    template<class T, class U>
    typename sum_t<T,U>::result_type sum_t<T,U>::operator()()
    {
    //    BOOST_AUTO_TPL(result, m_sum);
        return m_sum;
    }

    template<class T, class U>
    sum_t<T, U> make_sum(const T& t, const U& u)
    {
        return sum_t<T, U>(t, u);
    }

    // trying to cause ODR violation in a function template

    template<class T, class U>
    typename sum_t<T, U>::result_type sum(const T& t, const U& u)
    {
        BOOST_AUTO_TPL(result, t + u);
        return result;
    }

#elif !BOOST_WORKAROUND(BOOST_MSVC,==1300)

    template<class T, class U>
    class sum_t
    {
    public:
        typedef BOOST_TYPEOF_TPL(T() + U()) result_type;

        sum_t(const T& t, const U& u)
            : m_sum(t + u)
        {}
        BOOST_TYPEOF_TPL(T() + U()) operator()()
        {
            BOOST_AUTO_TPL(result, m_sum);
            return result;
        }
    private:
        BOOST_TYPEOF_TPL(T() + U()) m_sum;
    };

    template<class T, class U>
    sum_t<T, U> make_sum(const T& t, const U& u)
    {
        return sum_t<T, U>(t, u);
    }

    // trying to cause ODR violation in a function template

    template<class T, class U>
    typename sum_t<T, U>::result_type sum(const T& t, const U& u)
    {
        BOOST_AUTO_TPL(result, t + u);
        return result;
    }

#endif

#endif//ODR_HPP_INCLUDED
