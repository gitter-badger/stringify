#ifndef BOOST_STRINGIFY_V0_INPUT_TYPES_FTUPLE_HPP
#define BOOST_STRINGIFY_V0_INPUT_TYPES_FTUPLE_HPP

//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/stringify/v0/input_arg.hpp>
#include <boost/stringify/v0/ftuple.hpp>
#include <boost/stringify/v0/stringifier.hpp>
#include <initializer_list>

BOOST_STRINGIFY_V0_NAMESPACE_BEGIN
namespace detail {

template <typename CharT, typename ParentFTuple, typename ChildFTuple>
class ftuple_stringifier: public stringifier<CharT>
{

private:

    using composed_ftuple_type
    = boost::stringify::ftuple<ParentFTuple, ChildFTuple>;
    using input_arg = boost::stringify::v0::input_arg<CharT, composed_ftuple_type>;
    using ini_list_type = std::initializer_list<input_arg>;

public:

    using char_type   = CharT ;
    using ftuple_type = ParentFTuple;
    using input_type = ChildFTuple;
    using writer_type = boost::stringify::v0::output_writer<CharT>;;
    using second_arg = ini_list_type;

    ftuple_stringifier
        ( const ParentFTuple& parentF
        , const ChildFTuple& childF
        , ini_list_type args = {}
        )
        : m_fmt(boost::stringify::v0::make_ftuple(parentF, childF))
        , m_args(args)
    {
    }

    std::size_t length() const override
    {
        std::size_t sum = 0;
        for(const auto& arg : m_args)
        {
            sum += arg.length(m_fmt);
        }
        return sum;
    }

    int remaining_width(int w) const override
    {
        for(const auto& arg : m_args)
        {
            w += arg.remaining_width(w, m_fmt);
        }
        return w;
    }

    void write(writer_type& out) const override
    {
        for(const auto& arg : m_args)
        {
            arg.write(out, m_fmt);
        }
    }

private:

    composed_ftuple_type m_fmt;
    ini_list_type m_args;

};

template <typename ChildFtuple>
struct input_ftuple_traits
{
    template <typename CharT, typename FTuple>
    using stringifier =
        boost::stringify::v0::detail::ftuple_stringifier
        <CharT, FTuple, ChildFtuple>;
};

} // namespace detail

template <typename ... F>
boost::stringify::v0::detail::input_ftuple_traits<boost::stringify::v0::ftuple<F...>>
boost_stringify_input_traits_of(boost::stringify::v0::ftuple<F...> fmt);

BOOST_STRINGIFY_V0_NAMESPACE_END

#endif  // BOOST_STRINGIFY_V0_INPUT_TYPES_FTUPLE_HPP

