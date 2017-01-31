#ifndef BOOST_STRINGIFY_FMT_WIDTH_HPP
#define BOOST_STRINGIFY_FMT_WIDTH_HPP

//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/stringify/type_traits.hpp>


namespace boost {
namespace stringify {

typedef int width_t;

struct width_tag;


template <template <class> class Filter>
struct width_impl
{
    typedef boost::stringify::width_tag category;
    template <typename T> using accept_input_type = Filter<T>;    

    constexpr width_impl(boost::stringify::width_t v = 0)
        : m_value(v)
    {
    }

    constexpr width_impl(const width_impl& w) = default;

    constexpr boost::stringify::width_t width() const noexcept
    {
        return m_value;
    }
    
private:
    
    boost::stringify::width_t m_value;
};


template <boost::stringify::width_t Width, template <class> class Filter>
struct width_impl_t
{
    typedef boost::stringify::width_tag category;
    template <typename T> using accept_input_type = Filter<T>;    

    constexpr boost::stringify::width_t width() const noexcept
    {
        return Width;
    }
};


struct width_tag
{
    typedef
    boost::stringify::width_impl_t<0, boost::stringify::true_trait>
        default_impl;
};


template <template <class> class Filter = boost::stringify::true_trait>
constexpr auto width_if(boost::stringify::width_t w) noexcept
{
    return boost::stringify::width_impl<Filter>(w);
}


constexpr auto width(boost::stringify::width_t w) noexcept
{
    return boost::stringify::width_impl<boost::stringify::true_trait>(w);
}


} // namespace stringify
} // namespace boost

#endif  // BOOST_STRINGIFY_FMT_WIDTH_HPP

