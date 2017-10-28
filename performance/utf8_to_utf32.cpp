//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <locale>
#include <fstream>

#include <boost/stringify.hpp>
#include "loop_timer.hpp"


#define PRINT_BENCHMARK(label)  \
  BOOST_LOOP_TIMER(10000000000ll, label)

int main()
{
    namespace strf = boost::stringify::v0;
    
    std::string u8sample1(500, 'A');
    std::string u8sample2;
    std::string u8sample3;
    std::string u8sample4;
    for(int i = 0; i < 500; ++i) u8sample2.append(u8"\u0100");
    for(int i = 0; i < 500; ++i) u8sample3.append(u8"\u0800");
    for(int i = 0; i < 500; ++i) u8sample4.append(u8"\U00010000");


    char32_t u32output[100000];
    constexpr std::size_t u32output_size = sizeof(u32output) / sizeof(u32output[0]);
    char32_t* u32output_end = &u32output[u32output_size];

    PRINT_BENCHMARK("write_to(u32output) [{u8sample1}]")
    {
        strf::write_to(u32output) [{u8sample1}];
    }
    PRINT_BENCHMARK("write_to(u32output) [{u8sample2}]")
    {
        strf::write_to(u32output) [{u8sample2}];
    }
    PRINT_BENCHMARK("write_to(u32output) [{u8sample3}]")
    {
        strf::write_to(u32output) [{u8sample3}];
    }
    PRINT_BENCHMARK("write_to(u32output) [{u8sample4}]")
    {
        strf::write_to(u32output) [{u8sample4}];
    }

    std::locale::global(std::locale("en_US.utf8"));
    auto& codecvt = std::use_facet<std::codecvt<char32_t, char, std::mbstate_t>>(std::locale());
    const char* u8from_next = nullptr;
    char32_t* u32to_next = nullptr;

    strf::write_to(stdout) = {'\n'};

    PRINT_BENCHMARK("std::codecvt / u8sample1 to utf32")
    {                                                 
        std::mbstate_t mb{};
        codecvt.in
            ( mb
            , &*u8sample1.begin()
            , &*u8sample1.end()
            , u8from_next
            , u32output
            , u32output_end
            , u32to_next);
        *u32to_next = '\0';
    }

    PRINT_BENCHMARK("std::codecvt / u8sample2 to utf32")
    {                                                 
        std::mbstate_t mb{};
        codecvt.in
            ( mb
            , &*u8sample2.begin()
            , &*u8sample2.end()
            , u8from_next
            , u32output
            , u32output_end
            , u32to_next);
        *u32to_next = '\0';
    }
    PRINT_BENCHMARK("std::codecvt / u8sample3 to utf32")
    {                                                 
        std::mbstate_t mb{};
        codecvt.in
            ( mb
            , &*u8sample3.begin()
            , &*u8sample3.end()
            , u8from_next
            , u32output
            , u32output_end
            , u32to_next);
        *u32to_next = '\0';
    }
    PRINT_BENCHMARK("std::codecvt / u8sample4 to utf32")
    {                                                 
        std::mbstate_t mb{};
        codecvt.in
            ( mb
            , &*u8sample4.begin()
            , &*u8sample4.end()
            , u8from_next
            , u32output
            , u32output_end
            , u32to_next);
        *u32to_next = '\0';
    }

}