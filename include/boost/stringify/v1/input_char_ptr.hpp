#ifndef BOOST_STRINGIFY_V1_INPUT_CHAR_PTR
#define BOOST_STRINGIFY_V1_INPUT_CHAR_PTR

#include <algorithm>
#include <limits>
#include <boost/stringify/v1/custom_alignment.hpp>
#include <boost/stringify/v1/custom_width_calculator.hpp>


namespace boost {
namespace stringify {
inline namespace v1 {
namespace detail {

template <typename InputType, typename FTuple>
struct string_arg_format
   : public boost::stringify::v1::arg_format_common
       <string_arg_format<InputType, FTuple>>
{
    using width_t = boost::stringify::v1::width_t;
    using char_flags_type = boost::stringify::v1::char_flags<'<', '>', '='>;
    using input_type = InputType;
    using ftuple_type = FTuple;

    constexpr string_arg_format(int w, const char* f)
        : flags(f)
        , width(w)
    {
    }

    constexpr string_arg_format(const char* f)
        : flags(f)
        , width(-1)
    {
    }

    constexpr string_arg_format(int w)
        : width(w)
    {
    }

    char_flags_type flags;
    width_t width;
};


template<typename CharT, typename Output, typename FTuple>
class char_ptr_stringifier
{

private:

    using width_t = boost::stringify::v1::width_t;
    using width_tag = boost::stringify::v1::width_tag;
    using alignment_tag = boost::stringify::v1::alignment_tag;

public:

    using char_type  = CharT;
    using input_type = const CharT*;
    using output_type = Output;
    using ftuple_type = FTuple;
    using arg_format_type = boost::stringify::v1::detail::string_arg_format
        <input_type, FTuple>;

    char_ptr_stringifier
        ( const FTuple& fmt
        , const CharT* str
        , arg_format_type argfmt
        ) noexcept
        : m_fmt(fmt)
        , m_str(str)
        , m_len(std::char_traits<CharT>::length(str))
        , m_total_width(argfmt.get_width(fmt))
        , m_padding_width(padding_width())
        , m_alignment(argfmt.get_alignment(fmt))
    {
    }

    char_ptr_stringifier(const FTuple& fmt, const CharT* str) noexcept
        : m_fmt(fmt)
        , m_str(str)
        , m_len(std::char_traits<CharT>::length(str))
        , m_total_width(get_facet<width_tag>().width())
        , m_padding_width(padding_width())
        , m_alignment(get_facet<alignment_tag>().value())
    {
    }

    ~char_ptr_stringifier()
    {
    }

    std::size_t length() const
    {
        if (m_padding_width > 0)
        {
            return m_len +
                boost::stringify::v1::fill_length<CharT, input_type>
                (m_padding_width, m_fmt);
        }
        return m_len;
    }

    void write(Output& out) const
    {
        if (m_padding_width > 0)
        {
            if(m_alignment == boost::stringify::v1::alignment::left)
            {
                out.put(m_str, m_len);
                write_fill(out);
            }
            else
            {
                write_fill(out);
                out.put(m_str, m_len);
            }
        }
        else
        {
            out.put(m_str, m_len);
        }
    }


    int remaining_width(int w) const
    {
        if(m_total_width > w)
        {
            return 0;
        }
        if(m_padding_width > 0)
        {
            return w - m_total_width;
        }
        return
            boost::stringify::v1::get_width_calculator<input_type>(m_fmt)
            .remaining_width(w, m_str, m_len);
    }
    

private:

    const FTuple& m_fmt;
    const CharT* m_str;
    const std::size_t m_len;
    const width_t m_total_width;
    const width_t m_padding_width;
    boost::stringify::v1::alignment m_alignment;

    template <typename fmt_tag>
    decltype(auto) get_facet() const noexcept
    {
        return m_fmt.template get<fmt_tag, input_type>();
    }

    void write_fill(Output& out) const
    {
        boost::stringify::v1::write_fill<CharT, input_type>
                (m_padding_width, out, m_fmt);
    }

    width_t padding_width() const
    {
        return
            boost::stringify::v1::get_width_calculator<input_type>(m_fmt)
            .remaining_width(m_total_width, m_str, m_len);
    }
};


template <typename CharIn>
struct char_ptr_input_traits
{
private:

    template <typename CharOut>
    struct helper
    {
        static_assert(sizeof(CharIn) == sizeof(CharOut), "");

        template <typename Output, typename FTuple>
        using stringifier
        = boost::stringify::v1::detail::char_ptr_stringifier
            <CharOut, Output, FTuple>;
    };

public:

    template <typename CharT, typename Output, typename FTuple>
    using stringifier
    = typename helper<CharT>::template stringifier<Output, FTuple>;
};

} // namespace detail

boost::stringify::v1::detail::char_ptr_input_traits<char>
boost_stringify_input_traits_of(const char*);

boost::stringify::v1::detail::char_ptr_input_traits<char16_t>
boost_stringify_input_traits_of(const char16_t*);

boost::stringify::v1::detail::char_ptr_input_traits<char32_t>
boost_stringify_input_traits_of(const char32_t*);

boost::stringify::v1::detail::char_ptr_input_traits<wchar_t>
boost_stringify_input_traits_of(const wchar_t*);

} // inline namespace v1
} // namespace stringify
} // namespace boost



#endif  /* BOOST_STRINGIFY_V1_INPUT_CHAR_PTR */
