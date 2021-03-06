#include <boost/stringify.hpp>
#include <boost/assert.hpp>

int main()
{
    namespace strf = boost::stringify::v0;

    //[trivial_formatting_sample
    int value = 255;

    // write in hexadecimal
    auto result = strf::make_string [{value, " in hexadecimal is ", {value, /*<<
    `'#'` = show base, `'x'` = hexadecimal. >>*/"#x"}}];
    BOOST_ASSERT(result.value() == "255 in hexadecimal is 0xff");

    // with width equal to 6
    result = strf::make_string [{"----", {value, 6}, "----"}];
    BOOST_ASSERT(result.value() == "----   255----");

    // width and formatting string
    result = strf::make_string[{"----", {value, {6, /*<<
    `'<'` = justify left >>*/"<#x"}}, "----"}];
    BOOST_ASSERT(result.value() == "----0xff  ----");
    //]

    return 0;
}

