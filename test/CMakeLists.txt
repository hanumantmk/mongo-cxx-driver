enable_testing()

set(CMAKE_CXX_FLAGS "-DMONGOCXX_TESTING ${CMAKE_CXX_FLAGS}")

include_directories("include")

macro(test t)
    add_executable(test_${t} test_${t}.cpp)
    target_link_libraries(test_${t} mongocxx-mocked)
endmacro()

test(1)
add_test(test_suite_1 test_1)
test(3)
add_test(test_suite_3 test_3)
test(4)
add_test(test_suite_4 test_4)
test(5)
add_test(test_suite_5 test_5 10)

add_executable(test_driver
    main.cpp
    driver/base/bulk_write.cpp
    driver/base/client.cpp
    driver/base/collection.cpp
    driver/base/database.cpp
    driver/base/write_concern.cpp
    driver/base/private/write_concern.cpp
    driver/model/update_many.cpp
    driver/options/aggregate.cpp
    driver/result/insert_one.cpp
    driver/result/delete.cpp
    driver/result/replace_one.cpp
    driver/result/update.cpp
)
target_link_libraries(test_driver mongocxx-mocked)
add_test(driver test_driver)

add_executable(test_bson
    new_tests.cpp
    bson_builder.cpp
    bson_util_itoa.cpp
    bson_string_or_literal.cpp
)
target_link_libraries(test_bson mongocxx-mocked)
add_test(bson test_bson)
