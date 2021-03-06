#ifndef BOOST_STRINGIFY_V0_FACETS_WIDTH_HPP
#define BOOST_STRINGIFY_V0_FACETS_WIDTH_HPP

//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/stringify/v0/constrained_facet.hpp>

BOOST_STRINGIFY_V0_NAMESPACE_BEGIN

typedef int width_t;

struct width_tag;

struct width_impl
{
    typedef boost::stringify::v0::width_tag category;

    constexpr width_impl(boost::stringify::v0::width_t v = 0)
        : m_value(v)
    {
    }

    constexpr width_impl(const width_impl& w) = default;

    constexpr boost::stringify::v0::width_t width() const noexcept
    {
        return m_value;
    }
    
private:
    
    boost::stringify::v0::width_t m_value;
};


template <boost::stringify::v0::width_t Width>
struct width_impl_t
{
    typedef boost::stringify::v0::width_tag category;

    constexpr boost::stringify::v0::width_t width() const noexcept
    {
        return Width;
    }
};


constexpr width_impl_t<0> default_width {};       
       
struct width_tag
{
    constexpr static const auto& get_default() noexcept
    {
        return boost::stringify::v0::default_width;
    }
};


template <template <class> class Filter>
constexpr auto width_if(boost::stringify::v0::width_t w) noexcept
{
    return constrained_facet<Filter, width_impl>{w};
}


constexpr auto width(boost::stringify::v0::width_t w) noexcept
{
    return width_impl{w};
}


BOOST_STRINGIFY_V0_NAMESPACE_END

#endif  // BOOST_STRINGIFY_V0_FACETS_WIDTH_HPP

