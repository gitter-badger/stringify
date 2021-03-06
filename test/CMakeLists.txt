cmake_minimum_required (VERSION 3.0)
project (unit_tests)

include_directories("../../../")

add_executable(input_string_test_header_only      v0/input_string_test.cpp)
add_executable(input_int_test_header_only         v0/input_int_test.cpp)
add_executable(input_char_test_header_only        v0/input_char_test.cpp)
add_executable(input_char32_test_header_only      v0/input_char32_test.cpp)
add_executable(input_ftuple_test_header_only      v0/input_ftuple_test.cpp)
add_executable(join_test_header_only              v0/join_test.cpp)
add_executable(output_string_test_header_only     v0/output_string_test.cpp)
add_executable(output_char_ptr_test_header_only   v0/output_char_ptr_test.cpp)
add_executable(output_streambuf_test_header_only  v0/output_streambuf_test.cpp)
add_executable(output_FILE_test_header_only       v0/output_FILE_test.cpp)
add_executable(ftuple_merge_test_header_only      v0/ftuple_merge_test.cpp)

target_link_libraries(input_string_test_header_only      boost_stringify_header_only)
target_link_libraries(input_int_test_header_only         boost_stringify_header_only)
target_link_libraries(input_char_test_header_only        boost_stringify_header_only)
target_link_libraries(input_char32_test_header_only      boost_stringify_header_only)
target_link_libraries(input_ftuple_test_header_only      boost_stringify_header_only)
target_link_libraries(join_test_header_only              boost_stringify_header_only)
target_link_libraries(output_string_test_header_only     boost_stringify_header_only)
target_link_libraries(output_char_ptr_test_header_only   boost_stringify_header_only)
target_link_libraries(output_streambuf_test_header_only  boost_stringify_header_only)
target_link_libraries(output_FILE_test_header_only       boost_stringify_header_only)
target_link_libraries(ftuple_merge_test_header_only      boost_stringify_header_only)

add_test(run-input_string_test_header_only     input_string_test_header_only      )
add_test(run-input_int_test_header_only        input_int_test_header_only         )
add_test(run-input_char_test_header_only       input_char_test_header_only        )
add_test(run-input_char32_test_header_only     input_char32_test_header_only      )
add_test(run-input_ftuple_test_header_only     input_ftuple_test_header_only      )
add_test(run-join_test_header_only             join_test_header_only              )
add_test(run-output_string_test_header_only    output_string_test_header_only     )
add_test(run-output_char_ptr_test_header_only  output_char_ptr_test_header_only   )
add_test(run-output_streambuf_test_header_only output_streambuf_test_header_only  )
add_test(run-output_FILE_test_header_only      output_FILE_test_header_only       )
add_test(run-ftuple_merge_test_header_only     ftuple_merge_test_header_only      )




add_executable(input_string_test_static_lib      v0/input_string_test.cpp)
add_executable(input_int_test_static_lib         v0/input_int_test.cpp)
add_executable(input_char_test_static_lib        v0/input_char_test.cpp)
add_executable(input_char32_test_static_lib      v0/input_char32_test.cpp)
add_executable(input_ftuple_test_static_lib      v0/input_ftuple_test.cpp)
add_executable(join_test_static_lib              v0/join_test.cpp)
add_executable(output_string_test_static_lib     v0/output_string_test.cpp)
add_executable(output_char_ptr_test_static_lib   v0/output_char_ptr_test.cpp)
add_executable(output_streambuf_test_static_lib  v0/output_streambuf_test.cpp)
add_executable(output_FILE_test_static_lib       v0/output_FILE_test.cpp)
add_executable(ftuple_merge_test_static_lib      v0/ftuple_merge_test.cpp)

target_link_libraries(input_string_test_static_lib      boost_stringify)
target_link_libraries(input_int_test_static_lib         boost_stringify)
target_link_libraries(input_char_test_static_lib        boost_stringify)
target_link_libraries(input_char32_test_static_lib      boost_stringify)
target_link_libraries(input_ftuple_test_static_lib      boost_stringify)
target_link_libraries(join_test_static_lib              boost_stringify)
target_link_libraries(output_string_test_static_lib     boost_stringify)
target_link_libraries(output_char_ptr_test_static_lib   boost_stringify)
target_link_libraries(output_streambuf_test_static_lib  boost_stringify)
target_link_libraries(output_FILE_test_static_lib       boost_stringify)
target_link_libraries(ftuple_merge_test_static_lib      boost_stringify)

add_test(run-input_string_test_static_lib     input_string_test_static_lib      )
add_test(run-input_int_test_static_lib        input_int_test_static_lib         )
add_test(run-input_char_test_static_lib       input_char_test_static_lib        )
add_test(run-input_char32_test_static_lib     input_char32_test_static_lib      )
add_test(run-input_ftuple_test_static_lib     input_ftuple_test_static_lib      )
add_test(run-join_test_static_lib             join_test_static_lib              )
add_test(run-output_string_test_static_lib    output_string_test_static_lib     )
add_test(run-output_char_ptr_test_static_lib  output_char_ptr_test_static_lib   )
add_test(run-output_streambuf_test_static_lib output_streambuf_test_static_lib  )
add_test(run-output_FILE_test_static_lib      output_FILE_test_static_lib       )
add_test(run-ftuple_merge_test_static_lib     ftuple_merge_test_static_lib      )



