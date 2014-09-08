add_executable(new_tests
    new_tests.cpp
    bson_builder.cpp
    bson_util_itoa.cpp
    bson_string_or_literal.cpp
)
target_link_libraries(new_tests mongocxx-static)
