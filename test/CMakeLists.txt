enable_testing()

include_directories("include")

macro(test t)
    add_executable(test_${t} test_${t}.cpp)
    target_link_libraries(test_${t} mongocxx-shared)
endmacro()

test(1)
add_test(test_suite_1 test_1)
test(2)
add_test(test_suite_2 test_2)
test(3)
add_test(test_suite_3 test_3)
test(4)
add_test(test_suite_4 test_4)
test(5)
add_test(test_suite_5 test_5 10)

add_executable(new_tests
    new_tests.cpp
    bson_builder.cpp
    bson_util_itoa.cpp
    bson_string_or_literal.cpp
    collection.cpp
)
target_link_libraries(new_tests mongocxx-static)
