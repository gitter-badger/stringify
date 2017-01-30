#ifndef BOOST_STRINGIFY_INPUT_STD_STRING_HPP_INCLUDED
#define BOOST_STRINGIFY_INPUT_STD_STRING_HPP_INCLUDED

//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/stringify/input_char_ptr.hpp>
#include <string>
#include <type_traits>

namespace boost {
namespace stringify{
namespace detail {

template <class CharT, typename Traits, typename Output, class Formatting>
class std_string_stringifier
    : public boost::stringify::stringifier<CharT, Output, Formatting>
{
    typedef boost::stringify::stringifier<CharT, Output, Formatting> base;

public:
    typedef boost::stringify::detail::string_arg_formatting arg_format_type;
    typedef std::basic_string<CharT, Traits> input_type;
    typedef CharT char_type;
    typedef Output output_type;
    typedef Formatting ftuple_type;

   std_string_stringifier
        ( const Formatting& fmt
        , const input_type& str
        , arg_format_type argf
        ) noexcept
        : m_fmt(fmt)
        , m_str(str)
        , m_padding_width(padding_width(argf.get_width<input_type>(fmt)))
        , m_alignment(boost::stringify::get_alignment<input_type>(fmt, argf.m_flags))
    {
    }
    
    std_string_stringifier(const Formatting& fmt, const input_type& str) noexcept
        : m_fmt(fmt)
        , m_str(str)
        , m_padding_width
          (padding_width(boost::stringify::get_width<input_type>(fmt)))
        , m_alignment(boost::stringify::get_alignment<input_type>(fmt))
    {
    }

    virtual std::size_t length() const override
    {
        if (m_padding_width > 0)
        {
            return m_str.length() + 
                boost::stringify::fill_length<CharT, input_type>
                (m_padding_width, m_fmt);
        }
        return m_str.length();
    }

    void write(Output& out) const override
    {
        if (m_padding_width > 0)
        {
            if(m_alignment == boost::stringify::alignment::left)
            {
                out.put(&m_str[0], m_str.length());
                write_fill(out);
            }
            else
            {
                write_fill(out);
                out.put(&m_str[0], m_str.length());
            }
        }
        else
        {
            out.put(&m_str[0], m_str.length());
        }
    }


private:

    const Formatting& m_fmt;
    const input_type& m_str;
    const width_t m_padding_width;
    boost::stringify::alignment m_alignment;
    
    void write_fill(Output& out) const
    {
        boost::stringify::write_fill<CharT, input_type>
                (m_padding_width, out, m_fmt);
    }
    
    width_t padding_width(width_t total_width) const
    {
        return
            boost::stringify::get_width_calculator<input_type>(m_fmt)
            .remaining_width(total_width, &m_str[0], m_str.length());
    }
};


template <typename CharIn, typename CharTraits>
struct std_string_input_traits
{
private:

    template <typename CharOut>
    struct helper
    {
        static_assert(sizeof(CharIn) == sizeof(CharOut), "");

        template <typename Output, typename Formatting>
        using stringifier
        = boost::stringify::detail::std_string_stringifier
            <CharOut, CharTraits, Output, Formatting>;
    };

public:

    template <typename CharT, typename Output, typename Formatting>
    using stringifier
    = typename helper<CharT>::template stringifier<Output, Formatting>;
};

} // namespace detail


template
    < typename String
    , typename CharT = typename String::value_type
    , typename CharTraits = typename String::traits_type
    >
auto boost_stringify_input_traits_of(const String& str)
    -> std::enable_if_t
        < std::is_same<String, std::basic_string<CharT, CharTraits> >::value
        , boost::stringify::detail::std_string_input_traits<CharT, CharTraits>
        >;
/*    
    -> std::enable_if_t
        < std::is_same<typename CharTraits::char_type, CharT>::value
       && std::is_convertible<decltype(str[0]), const CharT&>::value
       && std::is_convertible<decltype(str.length()), std::size_t>::value
       && std::is_same
              < typename std::iterator_traits<typename String::iterator>::iterator_category
              , std::random_access_iterator_tag
              >::value  
        , boost::stringify::detail::std_string_input_traits<CharT, CharTraits>
        >;
*/


} // namespace stringify
} // namespace boost


#endif
