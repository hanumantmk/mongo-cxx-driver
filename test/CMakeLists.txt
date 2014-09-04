enable_testing()

macro(test t)
    add_executable(test_${t} test_${t}.cpp)
    target_link_libraries(test_${t} mongocxx-shared)
    add_test(test test_${t})
endmacro()

test(1)
test(2)
test(3)
test(4)
test(5)

add_executable(new_tests
    new_tests.cpp
    bson_builder.cpp
    bson_util_itoa.cpp
    bson_string_or_literal.cpp
    collection.cpp
)
target_link_libraries(new_tests mongocxx-static)
