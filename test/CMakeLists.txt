enable_testing()

set(CMAKE_CXX_FLAGS "-DMONGOCXX_TESTING ${CMAKE_CXX_FLAGS}")

include_directories("include")

macro(test t)
    add_executable(test_${t} test_${t}.cpp)
    target_link_libraries(test_${t} mongocxx-mocked)
endmacro()

test(1)
add_test(test_suite_1 test_1)

add_executable(test_model_update_many
    driver/model/update_many.cpp
)
target_link_libraries(test_model_update_many mongocxx-mocked)
add_test(model_update_many test_model_update_many)

test(3)
add_test(test_suite_3 test_3)
test(4)
add_test(test_suite_4 test_4)
test(5)
add_test(test_suite_5 test_5 10)

add_executable(test_options_aggregate
    driver/options/aggregate.cpp
)
target_link_libraries(test_options_aggregate mongocxx-mocked)
add_test(options_aggregate test_options_aggregate)

add_executable(test_bulk_write
    driver/base/bulk_write.cpp
)
target_link_libraries(test_bulk_write mongocxx-mocked)
add_test(bulk_write test_bulk_write)

add_executable(test_write_concern
    driver/base/write_concern.cpp
)
target_link_libraries(test_write_concern mongocxx-mocked)
add_test(test_write_concern test_write_concern)

add_executable(test_private_write_concern
    driver/base/private/write_concern.cpp
)
target_link_libraries(test_private_write_concern mongocxx-mocked)
add_test(test_private_write_concern test_private_write_concern)

add_executable(test_client
    driver/base/client.cpp
)
target_link_libraries(test_client mongocxx-mocked)
add_test(test_client test_client)

add_executable(new_tests
    new_tests.cpp
    bson_builder.cpp
    bson_util_itoa.cpp
    bson_string_or_literal.cpp
    collection.cpp
)
target_link_libraries(new_tests mongocxx-mocked)
